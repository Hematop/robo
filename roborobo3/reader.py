import os
import sys
import time
import numpy as np
import pandas as pd
import seaborn as sns
import datetime
import matplotlib.pyplot as plt
from glob import glob
from os import listdir, getcwd
from os.path import join, abspath
from scipy.stats import linregress

# utils involving reading files

def read(filepath):
	n = 10000
	if "." in filepath:
		return pd.read_csv(filepath, delim_whitespace=True, comment='#').tail(n) # can enforce dtype={"count": int, "size": int} or similar for speed if column names are known
	else:
		df = pd.DataFrame()
		fp = join(abspath(getcwd()), filepath, "*.txt")
		for fn in glob(fp):
			print('Reading from >'+fn)
			cr = pd.read_csv(fn, delim_whitespace=True, comment='#').tail(n) # can enforce dtype={"count": int, "size": int} or similar for speed if column names are known
			fn =  os.path.splitext(os.path.basename(fn))[0]
			#print('Calling it >'+fn)
			for cn in list(cr.columns.values):
			#	print("\t|"+(cn[:-1]+' '+fn))
				ncn = cn[:-1]+' '+fn
				if ncn in list(df.columns.values):
					ncn = ncn+'_'
				cr[ncn] = cr[cn]
				del cr[cn]
			df = df.append(cr, ignore_index=False)
		return df

def wai(path):
	fp = join(abspath(getcwd()), path, "*/datalog*.txt")
	for fn in sorted(glob(fp)):
		with open(fn) as f:
			print fn.split("/")[-2] + "\thas done: " + str(sum(1 for _ in f) - 14)
	fp = join(abspath(getcwd()), path, "*.txt")
	for fn in sorted(glob(fp)):
		with open(fn) as f:
			print fn.split("/")[-1] + "\thas done: " + str(sum(1 for _ in f) - 14)

def divide(df):
	n = len(df.index)/5
	ndf = pd.DataFrame()
	ndf['evenspaced'] = range(n)
	ndf['param'] = 0.
	for i in range(n):
		ndf['param'].iloc[i] = float(df['B'].iloc[i][-5:])
	for i in range(5):
		cn = df['A'].iloc[i*n]
		ndf[cn] = 0.
		for j in range(n):
			ndf[cn].iloc[j] = df['C'].iloc[i*n+j]
		if cn != 'groupDensity':
			ndf.plot(x = 'param', y = cn, style = 'o')
			plt.title(cn)
			#plt.axis([0,0.5,0,2000])
	plt.show()

def genericDivide(df):
	ndf = pd.DataFrame(columns={'param'})
	#0ndf['evenspaced'] = range(len(df.index))
	ndf['param'] = [0.]*(len(df.index))
	for i in range(len(df.index)):
		s = df['C'].iloc[i].split('_')
		if '.' in s[1]:
			ndf['param'].iloc[i] = float(s[1])
		else:
			ndf['param'].iloc[i] = float(s[0])
		cn = df['A'].iloc[i]
		if not cn in ndf.columns.values:
			ndf[cn] = -100.
		ndf[cn].iloc[i] = df['B'].iloc[i]
	for cn in ndf.columns.values:
		print('|'+cn+'|'+str(ndf[cn].dtype))
	fig, axes = plt.subplots(nrows=2, ncols=2, subplot_kw={'xlim': (0,0.2)})
	axes[0][0].title.set_text('attracted')
	axes[0][1].title.set_text('gAttracted')
	axes[1][0].title.set_text('inGroup')
	axes[1][1].title.set_text('perGroup')
	for cn in ndf.columns.values:
		if not ('groupDensity' in cn or cn == 'param'):
			ax = axes[0][0]
			if('gAttracted' in cn):
				ax = axes[0][1]
			else:
				if ('inGroup' in cn):
					ax = axes[1][0]
				else:
					if 'perGroup' in cn:
						ax = axes[1][1]

			ndf.plot(x = 'param', y = cn, style = 'o', ax=ax)
	axes[0][0].set_xlim([0,0.2])
	axes[0][1].set_xlim([0,0.2])
	axes[1][0].set_xlim([0,0.2])
	axes[1][1].set_xlim([0,0.2])
	plt.show()

def mashup(path):
	df = pd.read_csv(path, delim_whitespace=True, comment='#', dtype={"A": str, "B": str, "C": float})
	genericDivide(df)

def doAll(verbose):
	files = sys.argv[3:]
	avgs = pd.DataFrame(columns={'A','B','C'})
	for file in files:
		df = read(file)
		n = len(df.index)
		for cn in list(df.columns.values):
			m = df[cn][5000:].mean() # n/2
			if verbose == 'v':
				print(cn + '|'+ str(m))
			s = cn.split(' ')
			avgs.loc[len(avgs.index)] = [s[0],s[1],m]
	genericDivide(avgs)

def vios(verbose):
	files = sys.argv[3:]
	for file in files:
		tot = pd.DataFrame()
		df = read(file)
		n = len(df.index)
		for cn in list(df.columns.values):
			if 'attra' in cn:
				ncn = cn.split(' ')[1]

				tot[ncn] = df[cn]
				if verbose == 'v':
					print(ncn)
	axes = sns.violinplot(data=tot)
	plt.show()

def chp(filename, propertyname, newValue):
	verbose = False
	if(len(sys.argv)==6 and sys.argv[5]=='v'):
		verbose = True
	f_source = open(filename,"r")
	lines=f_source.readlines()
	f_source.close()

	f_target = open(filename,"w")
	changed = False
	for l in lines:
		if propertyname in l:
			f_target.write(propertyname+" = "+newValue+'\n')
			changed = True
			if verbose:
				print propertyname+" changed to "+str(newValue)
		else:
			f_target.write(l)
	if not changed:
		f_target.write(propertyname+" = "+newValue+'\n')
		if verbose:
			print propertyname+" added, with value "+str(newValue)
	f_target.close()

if len(sys.argv) < 3:
	print "Syntax: python reader.py <mode> [...]"
	print "\t1: get curve from one file containing averages"
	print "\t\tpython reader.py 1 <path>"
	print "\t2: whereAmI"
	print "\t\tpython reader.py 2 <path>"
	print "\t3: get curve from files containing evolution list"
	print "\t\tpython reader.py 3 v <path> [<other paths> [...]]"
	print "\t4: get violin plots from files containing evolution list"
	print "\t\tpython reader.py 4 v <path> [<other paths> [...]]"
	print "\t5: change property"
	print "\t\tpython reader.py 5 <path> <property> <new value> [v]"
else:
	if int(sys.argv[1]) == 1:
		mashup(sys.argv[2])
	if int(sys.argv[1]) == 2:
		wai(sys.argv[2])
	if int(sys.argv[1]) == 3:
		doAll(sys.argv[2])
	if int(sys.argv[1]) == 4:
		vios(sys.argv[2])
	if int(sys.argv[1]) == 5:
		chp(sys.argv[2], sys.argv[3], sys.argv[4])

