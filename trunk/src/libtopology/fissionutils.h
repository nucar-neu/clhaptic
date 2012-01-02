#ifndef FISSION_UTILS_H
#define FISSION_UTILS_H


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

void setup_gpu_queue(cl_context ctx, fission_topology * topo,bool enable_profiling);

#endif // __FISSION_UTILS_
