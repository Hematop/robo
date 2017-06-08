import os
import sys
import time
import numpy as np
import pandas as pd
import datetime
import matplotlib.pyplot as plt
from glob import glob
from os import listdir, getcwd
from os.path import join, abspath
from scipy.stats import linregress

# to plot some results stored in a log file



def readOneFile(filepath):
	return pd.read_csv(filepath, delim_whitespace=True, comment='#') # can enforce dtype={"count": int, "size": int} or similar for speed if column names are known

def readADirectory(dirpath):
	df = pd.DataFrame()
	fp = join(abspath(getcwd()), dirpath, "*.txt")
	for fn in glob(fp):
		print('Reading from >'+fn)
		cr = pd.read_csv(fn, delim_whitespace=True, comment='#') # can enforce dtype={"count": int, "size": int} or similar for speed if column names are known
		fn =  os.path.splitext(os.path.basename(fn))[0]
		#print('Calling it >'+fn)
		for cn in list(cr.columns.values):
		#	print("\t|"+(cn[:-1]+' '+fn))
			cr[cn[:-1]+' '+fn] = cr[cn]
			del cr[cn]
		df = df.append(cr, ignore_index=False)
	return df

def computeSlopes(df):
	slopes = pd.DataFrame()
	for cn in list(df.columns.values):
		if "size" in cn:
			nc = cn.replace("size", "mean")
			df[nc] = df[cn].rolling(20, win_type='boxcar').mean()
			sc = cn.replace("size", "slope")
			#slopes[sc] = pd.rolling_apply(df[nc], 21, lambda T: T[-1]-T[0]) # deprecated
			slopes[sc] = df[nc].rolling(center=False, window=21).apply(lambda T: T[-1]-T[0])
		del df[cn]
	return slopes

def divide(df):
	n = len(df.index)/5
	ndf = pd.DataFrame()
	ndf['evenspaced'] = range(n)
	ndf['param'] = 0.
	for i in range(n):
		ndf['param'].iloc[i] = float(df['C'].iloc[i][3:])
	for i in range(5):
		cn = df['A'].iloc[i*n]
		ndf[cn] = 0.
		for j in range(n):
			ndf[cn].iloc[j] = df['B'].iloc[i*n+j]
		if cn != 'groupDensity':
			ndf.plot(x = 'param', y = cn, style = 'o')
			plt.title(cn)
			#plt.axis([0,0.5,0,2000])



if len(sys.argv) == 1:
	print "Syntax: ", sys.argv[0], " <pathToFileOrDirectory>"
	quit()

path = sys.argv[1]
df = pd.DataFrame()
if(".txt" in path):
	df = readOneFile(path)
else:
	df = readADirectory(path)



#fig, axes = plt.subplots(nrows=2, ncols=1) # to show several subplots on one figure and choose on which one what column goes

#axes[2].hist(slopes[cn].dropna(), alpha=.4, bins=50) # example of hist plot
#slopes[cn].plot(kind='kde', ax=axes[1]) # example of kde plot
#plt.scatter(socz['x'], socz['y']) # example of scatter plot

#df = df.rolling(20, win_type='boxcar').mean()
#df = df.applymap(lambda x: 0 if np.isnan(x) else int(x/100))
#lone = df[df['dist']==1.0]
#del df['count']

#groupSizes = pd.DataFrame()
#endTimes = pd.DataFrame()
#groupRadii = pd.DataFrame()
ig = pd.DataFrame()
pg = pd.DataFrame()
at = pd.DataFrame()
ag = pd.DataFrame()
avgs = pd.DataFrame(columns={'A','B','C'})
averaging = 300
i = 0
for cn in list(df.columns.values):
	#print(cn)
	m = df[cn][5000:].mean() # 20000:-1
	#print(cn + ' '+ str(m))
	s = cn.split(' ')
	avgs.loc[i] = [s[0],s[1],m]
	i = i+1
	if 'inGroup' in cn:
		
		ig[cn.replace('inGroup','')] = ( df[cn] ).rolling(averaging, win_type='boxcar').mean() # / int(cn.replace('inGroup','')[1:5]) # .rolling(averaging, win_type='boxcar').mean()
	if 'perGroup' in cn:
		pg[cn.replace('perGroup','')] = df[cn].rolling(averaging, win_type='boxcar').mean()
	if 'attracted' in cn:
		at[cn.replace('attracted','')] = (df[cn] ).rolling(averaging, win_type='boxcar').mean() # (df[cn] ) # / int(cn.replace('attracted','')[1:5])
	if 'gAttracted' in cn:
		ag[cn.replace('gAttracted','')] = (df[cn] / df[cn.replace('gAttracted','inGroup')]).rolling(averaging, win_type='boxcar').mean()
print avgs
divide(avgs)
# keep data in indices range x:y:z # df[cn].iloc[x:y:z]

	#if not "group" in cn and not "radius" in cn:
	#	del df[cn]
	#if "group" in cn:
	#	raw = cn.replace("group", "")

	#	df['end'+raw] = df[cn].fillna(-10).rolling(center=True, window=51).apply(lambda T: 100 if np.isnan(T[25:-1]).any() or (T[0:25].mean() > T[25:-1].max()) else 0)
	#	groupSizes[raw] = df[cn]
	#	endTimes[raw] = df['end'+raw]
	#	groupRadii[raw] = df['radius'+raw]
		#df[cn].plot(ax=axes[1], legend=True)
		#df[cn] = df.applymap(lambda x: 0 if np.isnan(x) else int(x/100))
		#df['end'+raw].plot(ax=axes[1], legend=True)
	#if "radius" in cn:
		#df[cn].plot(ax=axes[0], legend=True)
#		df['LEA'+raw] = df[cn]*0
#		for i in range(2,len(df)):
#			if df['endA'+raw][len(df)-i] == 0:
#				df['LEA'+raw][len(df['LEA'+raw])-i] = 1+df['LEA'+raw][len(df['LEA'+raw])+1-i]
#			else:
#				df['LEA'+raw][len(df['LEA'+raw])-i] = 0
#		df['LEA'+raw].plot(ax=axes[3])
#		df.plot(x=cn, y='LEA'+raw, style='o', ax=axes[2])

#radius = np.sqrt( groupRadii / groupSizes )

#df.plot(colormap='cubehelix')
#groupSizes.plot(colormap='Set1')
#endTimes.plot(colormap='Set1')
#groupRadii.plot(colormap='Set1')
#radius.plot(colormap='Set1')


ig.plot(colormap='Set1')
#plt.axis([0,60000,0,3000])
plt.axis([0,60000,0,3000])
plt.title('N_robots_in_groups')
#plt.xlabel('time')


pg.plot(colormap='Set1')
plt.title('Average N_robots_per_groups')
plt.axis([0,60000,0,3000])
at.plot(colormap='Set1')
plt.title('N_attracted_robots')
plt.axis([0,60000,0,3000])
ag.plot(colormap='Set1')
plt.axis([0,60000,0,3000])
plt.title('N_attracted_robots / N_robots_in_groups')

'''
pg.plot(colormap='Set1')
plt.axis([0,60000,0,3000])
plt.title('Average N_robots_per_groups')
plt.xlabel('time')

at.plot(colormap='Set1')
plt.axis([0,60000,0,3000])
plt.title('N_attracted_robots')
plt.xlabel('time')

ag.plot(colormap='Set1')
plt.axis([0,60000,0,3000])
plt.title('N_attracted_robots / N_robots_in_groups')
plt.xlabel('time')
'''
plt.show()