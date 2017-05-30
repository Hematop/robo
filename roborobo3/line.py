#!/usr/bin/python
# to explore a segment of SW's phase diagram

import os
import sys
import datetime
import time

debug = False   # if True: shell command are not issued, but displayed.

def getTimestamp():
    return datetime.datetime.now().strftime("%Y%m%d_%H%M")

def createdir(directory):
	if not os.path.exists(directory):
        	if debug == False:
	                os.makedirs(directory)
	        print "[INFO] directory \"",directory,"\" created."
	else:
	        print "[ERROR] directory already exists."
	        quit()

def replaceProperty(filename, propertyname, newValue):
	f_source = open(filename,"r")
	lines=f_source.readlines()
	f_source.close()

	f_target = open(filename,"w")
	for l in lines:
		if propertyname in l:
			f_target.write(propertyname+" = "+newValue+'\n')
		else:
			f_target.write(l)
	f_target.close()


if len(sys.argv) == 1:
	print "Syntax: ", sys.argv[0], " <path/file.properties> <nb_of_replicates> [<changing_property> <initial_value> <end_value> <replicates_for_each_value>] [<suffix>]"	
	print "\texample: python line.py config/template_vanillaEE.properties 32 gInitialNumberOfRobots 50 225 4"
	quit()
else:
	propertiesfile = sys.argv[1]
	nbrep = int(sys.argv[2])
	if len(sys.argv) >= 7:
		propertyname = sys.argv[3]
		initial_value = int(sys.argv[4])
		end_value = int(sys.argv[5])
		replicates = int(sys.argv[6])
	else:
		propertyname = 'foo'
		initial_value = 0
		end_value = 0
		replicates = 0
	if len(sys.argv) %4 == 0:
		suffix = "_"+sys.argv[len(sys.argv)-1]
	else:
		suffix=""
v=str(initial_value)

prefix = "./logs/"+getTimestamp()+"_"+propertyname+suffix
createdir(prefix)

for i in range(nbrep):
	if replicates != 0 and i%replicates == 0:
		v = str(initial_value + i * (end_value - initial_value) / (nbrep - replicates))
		print "[INFO] ",propertyname," changing to ",v
		replaceProperty(propertiesfile,propertyname,v)
		if '_.' in propertiesfile:
			originalfile = propertiesfile.replace('_.', '.')
			command = "python initial.py " + originalfile + " " + propertiesfile + " 2"
		if debug == False:
			os.system(command)
		else:
			print command
	print "[INFO] Starting replicate #",i
	
	dirname = prefix + "/" + v.zfill(len(str(end_value))) + "_" + str(i).zfill(len(str(nbrep))) 
	
	createdir(dirname)
	

	command = "env SDL_VIDEODRIVER=dummy nohup ./roborobo -b -l " + propertiesfile + " -o " + dirname + " 1> " + dirname + "/output.stdout 2> " + dirname + "/output.stderr &"
	
	if debug == False:
		os.system(command)
	else:
		print command
	
	time.sleep(0.2)

print "[INFO] Terminated."
