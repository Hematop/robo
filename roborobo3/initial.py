# to set specific initial conditions for minirobots #

import os
from os import listdir
from os.path import isfile, join
import shutil
import errno
import sys
from random import *
import numpy as np
import math

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

def clusters(n):#not perfect yet
	inserted_text = ''
	m = n/25
	for i in range(m):
		x = randint(20,360)
		y = randint(20,360)
		for j in range(5):
			for k in range(5):
				inserted_text += robot( 25*i + 5*j + k, x + 3*j, y + 6*k + 3*(j%2) )
	return inserted_text

def packed(n):
	inserted_text = ''
	m = np.sqrt(n)
	for i in range(n):
		x,y = divmod(i,m)
		x = 50 + 3 * x
		y = 50 + 6 * y + 3*(x%2)
		inserted_text += robot(i,x,y)
	return inserted_text

def ring(n):
	inserted_text = ''
	c = int(findProperty(source,'gScreenWidth'))/2
	t = 0.1
	for i in range(n):
		x = c + t * math.cos(t)
		y = c + t * math.sin(t)
		inserted_text += robot(i,x,y)
		t += 5 / t
	return inserted_text

def spiral(n):
	inserted_text = ''
	c = int(findProperty(source,'gScreenWidth'))/2
	t = 0.1
	for i in range(n):
		x = c + t * math.cos(t)
		y = c + t * math.sin(t)
		inserted_text += robot(i,x,y)
		t += 5 / (1+t)
	return inserted_text

def robot(i,x,y):
	return( 'robot['+str(i)+'].x = '+str(x)+'\nrobot['+str(i)+'].y = '+str(y)+'\n' )

if len(sys.argv) < 4:
	print "Syntax: ", sys.argv[0], ''' <source> <target> <shape>\n
	\t1: spread grid
	\t2: packed
	\t3: random clusters
	\t4: packed ring
	\t5: packed spiral'''
	quit()
else:
	source = sys.argv[1]
	target = sys.argv[2]
	type = int(sys.argv[3])
	
	if target[-1:] == "/":
		target = target[:-1]
	if source[-1:] == "/":
		source = source[:-1]
	copy(source, target)
	n = int(findProperty(source,'gInitialNumberOfRobots').split('.')[0])

	inserted_text = ''
	if type == 1:
		inserted_text = grid(n)
	if type == 2:
		inserted_text = packed(n)
	if type == 3:
		inserted_text = clusters(n)
	if type == 4:
		inserted_text = ring(n)
	if type == 5:
		inserted_text = spiral(n)
	tag = "#//###TAG:INIT###//#"
	insertInFile(target,tag,inserted_text)
