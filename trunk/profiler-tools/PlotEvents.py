import os
import sys
import glob
import re
import csv
import operator

# Imports for plotting
import matplotlib
matplotlib.use('gtkagg')
import matplotlib.pylab as pylab
import matplotlib.patches as patches
import matplotlib.pyplot as pyplot
import numpy as np

colorlist=['g','b','c','r','m','k','y','w']
EPSILON = 0.00000001

# List of event types to exclude from plots (e.g. Compile)
excludeList = []
tracePlots = True
perfPlots = True

# This class holds the information from an OpenCL event
class Event:
   def __init__(self, name, start, end):
      self.name = name  # TODO change this to 'name'
      self.start = float(start)/1e6  # convert to ms
      self.end = float(end)/1e6      # convert to ms
      self.time = self.end-self.start
   
   def __str__(self):
      return 'Event: \n\tName: %s\n\tTime: %f' % (self.name, self.end-self.start)	
      
# This class holds the information related to the OpenCL host 
# that was printed in the dum
class Info: 
   def __init__(self, desc):
      self.desc = desc[0]
   
   def __str__(self):
      return self.desc
 
# This class defines an eventlist as a type (IO, kernel, etc) and 
# a list of events (i.e., it will be one row on the bar plot
class EventList:

   def __init__(self, type):
      self.type = type
      self.events = []
      self.total = None
   
   def __str__(self):
      return self.type
      
# An EventGroup combines all events and info from a single dumped file
class EventGroup:
   def __init__(self):
      self.filename = None
      self.infolist = []
      self.eventlists = []
      
   def __str__(self):
      return "Event group for %s" % self.filename	
   
   def getDescription(self):
      return self.infolist[0].__str__()

# print usage information
def printUsage():

   print '\nUsage: PlotEvents.py <eventDir> [-e eventType] [-np] [-nt]'
   print '\t<eventDir>: Directory containing event files'
   print '\t-e <type>:  Excludes an event type from plotting (e.g. Compile)'
   print '\t-np:        Dont generate performance plots'
   print '\t-nt:        Dont generate trace plots' 
   print '\nExample: PlotEvents.py ../EventDumps -e Compile -e IO -np'
   
# This can probably go into a class function later
def searchForEvent(name, eventList):

   for event in eventList.events:
      if event.name == name:
         return event
         
   return []
         
# This function parses the events out of each file and builds
# a list of each event type.  It returns a list of event lists.
def parse(filename):

   print('Parsing %s' % filename)
 
   # List containing the types of events we've seen so far
   uniqueTypes = []
 
   # Create a new event group for each file
   eventGroup = EventGroup()
   eventGroup.filename = filename;
   
   # Open the file and read in the lines
   lines = open(filename, 'r').readlines()
   
   # Create a tokenizer using a semicolon delimiter
   tokenizer = re.compile(r'\;')
   
   # Parse out all of the 'Info' lines
   newlines = []  # Lines not containing 'Info'
   for line in lines:
      
      # Tokenize the line
      tokens = tokenizer.split(line)
      
      # Store the line appropriately based on the contents
      if tokens[0] == 'Info':
         eventGroup.infolist.append(Info([tokens[1].strip()]))
      else:
         newlines.append(line)

   # Create an EventList object for each unique type of event
   for line in newlines:
   
      # Tokenize the line
      tokens = tokenizer.split(line)
      
      if not tokens[0] in excludeList:
         if not tokens[0] in uniqueTypes:
            uniqueTypes.append(tokens[0])
            eventGroup.eventlists.append(EventList(tokens[0]))
            
         index = uniqueTypes.index(tokens[0])
         eventGroup.eventlists[index].events.append(Event(tokens[1].strip(), tokens[4].strip(), tokens[5].strip()))

   print 'Unique types = %s' % uniqueTypes
   
   return eventGroup
   
# Given a list, return a list with all duplicates removed
def uniquify(seq):

    # Uniquify the list (order preserving)
    noDupes = []
    [noDupes.append(i) for i in seq if not noDupes.count(i)]
    return noDupes
   
# Calculate sums of each event type so we can see the aggregate time.
# For example: all kernels on a certain device took a total of N ms.
def computeTotals(allGroups):
   
   # For each event type, calculate the sum of all events so we
   # can plot a 'total' bar
   for eventGroup in allGroups: 
      for eventType in eventGroup.eventlists:
         sum = 0
         for event in eventType.events:
            sum = sum + event.time
         eventType.total = sum
 
# Get the events from all lists and create a event group 
# that can be used for plotting
def getMasterLists(allGroups):
 
   eventDescriptions = []
   typeList = []

   # Get a unique list of types
   for eventGroup in allGroups:
      for eventType in eventGroup.eventlists:
         typeList.append(eventType.type)
   typeList = uniquify(typeList)
   
   # We want to plot events with the same name in the same bar chart, so
   # we need to create a master list of all the event names
   index = 0
   for type in typeList:
      eventDescriptions.append([])
      eventDescriptions[index].append(type)
      for eventGroup in allGroups:
         for eventList in eventGroup.eventlists:
            if eventList.type == type:
               for event in eventList.events:
                  eventDescriptions[index].append(event.name)
      eventDescriptions[index] = uniquify(eventDescriptions[index])
      index += 1

   return eventDescriptions

def roundUp(value):
   
   return (int(value/0.5)+1)*0.5;

# Parse the command line input arguments
def parseCmdArgs(args):

   for i in range(1, len(args)):   
      if args[i] == '-e':
         print 'Excluding event type: %s' % args[i+1]
         global excludeList
         excludeList.append(args[i+1])
      if args[i] == '-nt':
         print 'Not creating trace plots'
         global tracePlots
         tracePlots = False
      if args[i] == '-np':
         print 'Not creating performance plots'
         global perfPlots
         perfPlots = False
         
#-------------------------------------------------------
#            Main program starts here
#-------------------------------------------------------

# Read in the files from disk and parse each one into event groups
path = None

if len(sys.argv) <= 1:
   print 'Not enough command line arguments!'
   printUsage()
   exit(-1)

path = sys.argv[1]   
parseCmdArgs(sys.argv)

eventGroups = []

eventFiles = glob.glob(os.path.join(path, '*.eventlog'))

if len(eventFiles) == 0:
   print 'No event files found in directory "%s"' % path
   exit(0)
   
for infile in eventFiles:
   print('Found %s' % infile)
   eventGroups.append(parse(infile))

numEventGroups = len(eventGroups)
   
# Exit if no event groups were found
if numEventGroups == 0:
   print('No event groups found')
   exit(0);

computeTotals(eventGroups)
masterLists = getMasterLists(eventGroups)

#---------------------------------------------------------------
#                      TRACE PLOTS
#---------------------------------------------------------------
if tracePlots:

   # Make a new figure
   figure = pyplot.figure(figsize=(16,8), facecolor='w')
   figure.clear()  
   figure.suptitle('Trace Plot', size=18)
   ax = figure.add_subplot(111)      

   yticks=[]
   yticklabels=[]

   # The max time (based on all events) will be used to determine 
   # the range of the plot
   maxTime = 0
   for group in eventGroups:
      for eventType in group.eventlists:
         for event in eventType.events:
            if event.end > maxTime:
               maxTime = event.end

   # All plots need to be made to be made relative to their respective start times     
   groupOffset = 0
   for group in eventGroups:
      
      typeCtr = 0
      
      # Plot based on the masterList ordering.  If a list type is in the master
      # list, but not in this specific list, plot an empty line (to keep colors
      # consistent)
      for type in masterLists:
         typeIndex = -1
         # Look to see if the type is present in this event group
         for i in range(0, len(group.eventlists)):
            if type[0] == group.eventlists[i].type:
               # Type was found
               typeIndex = i
      
         eventList = []
         if typeIndex >= 0:
               # Type is present in this event group
               
               # For each event, add it to its appropriate list type (kernels, IO, etc.)
               # and adjust it's time to be relative to the min
               for event in group.eventlists[typeIndex].events:
                  eventList.append((event.start, event.time))
         
         # Add this event type to the plot
         ax.broken_barh(eventList, (groupOffset, 1), facecolors=colorlist[typeCtr])
      
         # Add the type to the y-axis
         yticklabels.append(type[0])

         typeCtr += 1
         groupOffset += 1
         
      # Add the device name to the y-axis
      yticklabels.append(group.getDescription())
      groupOffset = groupOffset + 1
         
   # Set the plot range, tick marks, grid, etc.
   ax.set_ylim(0, groupOffset)
   ax.set_xlim(0, maxTime)
   ax.set_xlabel('time from start (ms)')
   ax.set_yticks([i+0.5 for i in range(0,groupOffset)]) 
   ax.set_yticklabels(yticklabels) 
   ax.xaxis.grid(True)
      
   pyplot.show()

#---------------------------------------------------------------
#                      PERFORMANCE PLOTS
#---------------------------------------------------------------
if perfPlots:

   patches = ['']*numEventGroups

   # Iterate over the different types of events (e.g. IO, kernel, etc)
   for eventType in masterLists:
      
      print '\n**** EVENT TYPE: %s ****' % eventType[0]
      # Make a new figure
      figure = pyplot.figure(figsize=(16,8), facecolor='w')
      figure.clear()
      
      chartTitle = '%s Events' % eventType[0]
         
      figure.suptitle(chartTitle, size=18)
      pyplot.rc('font', size=8)
      
      # Add a subplot for each of the events

      # Compute the number of subplots and their dimensions
      numEvents = len(eventType);
      chartsPerRow = 8
      cols = chartsPerRow
      if numEvents < chartsPerRow:
         cols = numEvents;
      displayCols = cols+1
      rows = numEvents/chartsPerRow
      if numEvents % chartsPerRow != 0:
         rows += 1

      eventCtr = 0
      displayCtr = 1

      index = -1
      # Iterate over the events in each event type (e.g. copyToBuffer in IO)
      # and plot all of the occurrences of each on the same chart
      for refEvent in eventType:
         
         index = index + 1
         if index == 0:
            continue
         
         # This leaves the last column empty to allow for the legend
         if displayCtr % displayCols == 0:
            displayCtr += 1
         
         # Plot the subplot
         ax = figure.add_subplot(rows, displayCols, displayCtr)

         # Set the X ticks
         numBars = len(masterLists)
         ax.set_xticks([x + 0.5 for x in range(0, numBars)])
         ax.set_xticklabels(range(1, numBars+1))
         ax.set_xlabel('Event %d:\n%s' % (eventCtr, refEvent))

         barCtr = 0
         maxY = 0

         print refEvent
         
         # For each event group, search to see if the event is present
         # If so, add it to the plot
         for eventGroup in eventGroups:
            eventTypeFound = False
            # Iterate over the different type of events until we
            # find the type that matches the target event
            for eventList in eventGroup.eventlists:
               # Check if the event type is present in this group
               if eventList.type == eventType[0]:
                  eventTypeFound = True
                  # Event type exists, now see if the specific event is present
                  # in this list
                  event = searchForEvent(refEvent, eventList)
                  if event != []:
                     print '\t%s: %s' % (eventGroup.getDescription(), event.time)
                     # Specific event was found in this list, add it to the plot
                     if event.time == 0:
                        # The chart will not plot 0
                        event.time = EPSILON
                     if event.time > maxY:
                        maxY = event.time
                     patches[barCtr] = pyplot.bar(barCtr, event.time, width=1.0, color=colorlist[barCtr])
                  else:
                     # Event does not exist in this list, add an empty bar
                     patches[barCtr] = pyplot.bar(barCtr, EPSILON, width=1.0, color=colorlist[barCtr])
                  barCtr += 1
            # Check to see if the target type of group was present at all
            if not eventTypeFound:
               # Event type does not exist for this event group, need to 
               # add an empty bar for the event
               patches[barCtr] = pyplot.bar(barCtr, EPSILON, width=1.0, color=colorlist[barCtr])
               barCtr += 1
         
         # Set the Y ticks
         maxY = roundUp(maxY)
         ax.set_yticks([0, maxY/2, maxY])
         ax.set_yticklabels([0, maxY/2, maxY])
         ax.set_ylim(0,maxY)
         ax.set_ylabel('time (ms)')
         
         displayCtr += 1
         eventCtr += 1

      figure.subplots_adjust(hspace=1.0, wspace=1.0)

      legendStrs = []
      for group in eventGroups:
         legendStrs.append(group.getDescription())
      leg_prop = matplotlib.font_manager.FontProperties(size=8)
      figure.legend((patches), legendStrs, 'right', prop=leg_prop)
         
      pyplot.show()

print('Done')
