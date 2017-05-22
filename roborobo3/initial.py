#!/usr/bin/python
import os
from os import listdir
from os.path import isfile, join
import shutil
import errno
import sys
from random import *
import numpy as np

debug = False   # if True: shell command are not issued, but displayed.

def insertInFile(filename,tag,text_to_insert):
	f_source = open(filename,"r")
	lines=f_source.readlines()
	f_source.close()
	    
	f_target = open(filename,"w")
	for l in lines:
		if tag in l:
			f_target.write(text_to_insert)
		f_target.write(l)
	f_target.close()

def findProperty(filename,propertyname):
	f_source = open(filename,"r")
	lines=f_source.readlines()
	f_source.close()

	for l in lines:
		if propertyname in l:
			print l.replace(' = ',' is: ')
			return l.replace(propertyname+' = ','')
	
	return ''

# copy file or directory (full content)
# from: http://www.pythoncentral.io
def copy(source, target):
	try:
		IGNORE_PATTERNS = ('.svn','CVS','.git','.test')
		shutil.copytree(source, target,ignore=shutil.ignore_patterns(*IGNORE_PATTERNS))
	except OSError as e:
		# If the error was caused because the source wasn't a directory
		if e.errno == errno.ENOTDIR:
			shutil.copy(source, target)
		else:
			print('%s' % e)

def grid(n):
	inserted_text = ''
	m = np.sqrt(n)
	for i in range(n):
		x,y = divmod(i,m)
		x = 10 + 380 * x / m
		y = 10 + 380 * y / m
		inserted_text += robot(i,x,y)
	return inserted_text

def packed(n):
	inserted_text = ''
	m = np.sqrt(n)
	for i in range(n):
		x,y = divmod(i,m)
		x = 100 + 3 * x
		y = 100 + 6 * y + 3*(x%2)
		inserted_text += robot(i,x,y)
	return inserted_text

def robot(i,x,y):
	return( 'robot['+str(i)+'].x = '+str(x)+'\nrobot['+str(i)+'].y = '+str(y)+'\n' )

if len(sys.argv) != 3:
	print "Syntax: ", sys.argv[0], " <source> <target>"
	quit()
else:
	source = sys.argv[1]
	target = sys.argv[2]
	#n = int(sys.argv[3])
	
	if target[-1:] == "/":
		target = target[:-1]
	if source[-1:] == "/":
		source = source[:-1]
	copy(source, target)
	n = int(findProperty(source,'gInitialNumberOfRobots'))

	inserted_text = packed(n)
	tag = "#//###TAG:INIT###//#"
	insertInFile(target,tag,inserted_text)
