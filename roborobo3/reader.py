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

# utils involving reading files


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

def mashup(path):
	df = pd.read_csv(path, delim_whitespace=True, comment='#', dtype={"A": str, "B": str, "C": float})
	divide(df)
	plt.show()

if len(sys.argv) != 3:
	print "Syntax: python reader.py <mode> <path>"
	print "\tmode 1: mashup"
	print "\tmode 2: whereAmI"
else:
	if int(sys.argv[1]) == 1:
		mashup(sys.argv[2])
	if int(sys.argv[1]) == 2:
		wai(sys.argv[2])

