import os
import sys
import numpy as np
from pandas import *
from pylab import *
import matplotlib.pyplot as plt
import matplotlib.patches as pat


if len(sys.argv)<=3:
	print("Usage: python haptic_cmdq.py <path to file/eventdump_cmdq1.log> <path to file/eventdump_cmdq2.log>")
	sys.exit(0)
command=("./event_edit.sh %s %s") % (sys.argv[1],sys.argv[2])
os.system(command) 
d1=read_csv('event_main.csv')
d2=read_csv('event_ad.csv')

d1temp=d1.Queue[0]
d2temp=d2.Queue[0]

div = 1000000.0

#Data Gathering and formatting using data structures from PANDAS
d1['Queue']=d1['Queue'] - d1temp
d1['Submit']=d1['Submit'] - d1temp
d1['Start']=d1['Start'] - d1temp
d1['End']=d1['End'] - d1temp

d2['Queue']=d2['Queue'] - d2temp
d2['Submit']=d2['Submit'] - d2temp
d2['Start']=d2['Start'] - d2temp
d2['End']=d2['End'] - d2temp

d2['Queue'] = d2['Queue']=d2['Queue']+ d1.Queue[(d2.Events[0])]
d2['Submit'] = d2['Submit']=d2['Submit']+ d1.Queue[(d2.Events[0])]
d2['Start'] = d2['Start']=d2['Start']+ d1.Queue[(d2.Events[0])]	
d2['End'] = d2['End']=d2['End']+ d1.Queue[(d2.Events[0])]



#Figure Plot for the Command Queue Execuion times
fig = plt.figure()
ax = fig.add_subplot(111)
for i in d1.index:
	if (d1.Type[i] == 'Kernel'):
		ax.plot(d1.Queue[i]/div, 7.5,'r+')
		
ax.broken_barh([ (d1.Queue[0]/div,d1.End[max(d1.index)]/div)] , (5, 5),label='box1', facecolors=(1,1,1,0))

for i in d2.index:
	ax.broken_barh([ (d2.Queue[i]/div,(d2.End[i]/div)-d2.Queue[i]/div)] , (10, 5),label='box2',facecolors=('red'))
ax.set_ylim(5,35)
#ax.set_xlim(0,200)
ax.set_xlabel('Time in ms ')
ax.set_yticks([7.5,12.5])
ax.set_yticklabels(['Cmd_Que1', 'Cmd_Que2'])
#ax.grid(True)
plt.title('Command Queue Execution Time')
savefig('Cmd_que_exec_time.eps')



