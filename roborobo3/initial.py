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

def robot(i,n):
	m = np.sqrt(n)
	x,y = divmod(i,m)
	x = 50 + 300 * x / m
	y = 50 + 300 * y / m
	return( 'robot['+str(i)+'].x = '+str(x)+'\nrobot['+str(i)+'].y = '+str(y)+'\n' )
	#robot[3].x = 120
	#robot[3].y = 80

if len(sys.argv) != 4:
	print "Syntax: ", sys.argv[0], " <source> <target> <nb_of_robots> {<directory_suffix>}"
	quit()
else:
	source = sys.argv[1]
	target = sys.argv[2]
	n = int(sys.argv[3])
	
	if target[-1:] == "/":
		target = target[:-1]
	if source[-1:] == "/":
		source = source[:-1]

	copy(source, target)
	tag = "#//###TAG:INIT###//#"
	for i in range(n):
		inserted_text = robot(i,n)
		insertInFile(target,tag,inserted_text)
