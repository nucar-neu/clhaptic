import fir_pb2

import pygtk
pygtk.require('2.0')
import gtk

#compute_stage = fir_pb2.stage()
#compute_stage_2 = fir_pb2.stage()

myfilter = fir_pb2.pipeline()
compute_stage = myfilter.fir_stg_1 
compute_stage_2 = myfilter.fir_stg_2 

compute_stage.name = "foo"
compute_stage.id = 100
compute_stage_2.name = "bar"
compute_stage_2.id = 200

print myfilter.fir_stg_1.name
print myfilter.fir_stg_2.name



window = gtk.Window(gtk.WINDOW_TOPLEVEL)

#Create a BOX for each stage
button_0 = gtk.Button("Stage 0")
button_1 = gtk.Button("Stage 1")
window.add(button_0)
button_0.show()
window.show()
gtk.main()
#window.add(button_1)
#Define Insertion Locations for Devices

#Define Performance Analysis Details

#Write out resultant messages


