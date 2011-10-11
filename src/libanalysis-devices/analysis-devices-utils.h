/**
 * \file Utilities reqd for analysis_device
 * Borrowed from clutils of SURF
 */


#ifndef __ANALYSIS_DEVICES_UTILS_H_
#define __ANALYSIS_DEVICES_UTILS_H_

#include <CL/cl.h>

#define EXITERROR 1

#define DONTEXITERROR 0

#define UNKNOWNSIZE -999

#define UNKNOWN -999

bool rand_zero_or_one();

//! Allocate pinned memory
cl_mem ad_allocBufferPinned(size_t mem_size,cl_context ctx );

void ad_setKernelArg(cl_kernel kernel, unsigned int index, size_t size, void* data);

int ad_errChk(const cl_int status, const char * msg, bool exitOnErr = 0);

void ad_sync(cl_command_queue queue);


#endif //ANALYSIS_DEVICES_UTILS_H

