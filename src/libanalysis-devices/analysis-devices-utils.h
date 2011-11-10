/**
 * \file Utilities reqd for analysis_device
 * Borrowed from clutils of SURF
 */


#ifndef __ANALYSIS_DEVICES_UTILS_H_
#define __ANALYSIS_DEVICES_UTILS_H_

#include <CL/cl.h>
#include "opencl_utils.h"


//! Allocate pinned memory
cl_mem ad_allocBufferPinned(size_t mem_size,cl_context ctx );

void ad_setKernelArg(cl_kernel kernel, unsigned int index, size_t size, void* data);



void ad_sync(cl_command_queue queue);

//unsigned int idivup(unsigned int , unsigned int);

#endif //ANALYSIS_DEVICES_UTILS_H

