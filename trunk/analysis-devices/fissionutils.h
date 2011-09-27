#include <iostream>
#include <vector>

#include <sstream>
#include <string>
#include <CL/cl.h>

//#include "profiler/clutils.h"

class fission_topology;

void setup_fission(fission_topology *);

void setup_fission_pipeline(  fission_topology * topo);

void setup_baseline(fission_topology * topo);

void list_all_opencl_devices();

bool check_for_extensions(char * ext_name, int deviceId, cl_device_id * rootDevices);

void    multi_device_single_context(fission_topology *);
