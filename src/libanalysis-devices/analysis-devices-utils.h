/**
 * \file Utilities reqd for analysis_device
 * Borrowed from clutils of SURF
 */


#ifndef __ANALYSIS_DEVICES_UTILS_H_
#define __ANALYSIS_DEVICES_UTILS_H_

#include <CL/cl.h>
#include "opencl_utils.h"


void ad_sync(cl_command_queue queue);

//unsigned int idivup(unsigned int , unsigned int);

#endif //ANALYSIS_DEVICES_UTILS_H

