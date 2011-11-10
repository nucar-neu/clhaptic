#ifndef __OPENCL_UTILS_H_
#define __OPENCL_UTILS_H_

#include "string.h"

#include <CL/cl.h>


#define EXITERROR 1

#define DONTEXITERROR 0

#define UNKNOWNSIZE -999

#define UNKNOWN -999


bool rand_zero_or_one();

int ad_errChk(const cl_int status, const char * msg, bool exitOnErr = 0);

bool check_for_extensions(char * ext_name, int deviceId, cl_device_id * device_list);

void ad_setKernelArg(cl_kernel kernel, unsigned int index, size_t size,
                     void* data);

void list_all_opencl_devices();                     


#endif // _OPENCL_UTILS_H_
