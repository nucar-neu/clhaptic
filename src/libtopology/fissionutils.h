#include <iostream>
#include <vector>

#include <sstream>
#include <string>
#include <CL/cl.h>

#include "opencl_utils.h"

class fission_topology;

void setup_fission(fission_topology *);

void setup_root_queue(fission_topology * topo, bool enable_profiling );

void setup_fission_pipeline(  fission_topology * topo);

void setup_baseline(fission_topology * topo);

void multi_device_single_context(fission_topology *);
