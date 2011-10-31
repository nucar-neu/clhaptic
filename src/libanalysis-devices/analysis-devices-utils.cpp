#include <stdio.h>
#include <CL/cl.h>
#include "analysis-devices-utils.h"
#include "eventtypes.h"
#include <cmath>
#include <iostream>
#include <ctime>

#define MAX_ERR_VAL 64

/**
 * A toy function that generates a random 0 or 1 sequence.
 * Used to test profiler stuff
 */
bool rand_zero_or_one()
{
	srand((unsigned)time(NULL));
	float val =((float) rand() / (RAND_MAX)) ;

	int k = round(val);
 	if(k == 0)
		return DISABLED;
	else
	{
		if (k == 1)
			return ENABLED;
		else
		{
			printf("a bug");
			exit(-1);
		}

	}

}

//! Allocate a buffer on device pinning the host memory at host_ptr
/*!
    \param mem_size Size of memory in bytes
    \return Returns a cl_mem object that points to pinned memory on the host
*/
cl_mem ad_allocBufferPinned(size_t mem_size,cl_context ctx )
{
    cl_mem mem;
    cl_int status;

   	mem = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,
                         mem_size, NULL, &status);


    ad_errChk(status, "Error allocating pinned memory", true);

    return mem;
}


//! Set an argument for a OpenCL kernel
/*!

\param kernel The kernel for which the argument is being set
\param index The argument index
\param size The size of the argument
\param data A pointer to the argument
*/
void ad_setKernelArg(cl_kernel kernel, unsigned int index, size_t size,
                     void* data)
{
    cl_int status;
    status = clSetKernelArg(kernel, index, size, data);
    if(status != CL_SUCCESS)
    	printf("Error in Arg No %d\n",index);
    ad_errChk(status, "Setting kernel arg", true);
}




//! OpenCl error code list
/*!
    An array of character strings used to give the error corresponding to the error code \n

    The error code is the index within this array
*/
char *cl_err_msg[MAX_ERR_VAL] = {
    "CL_SUCCESS",                         // 0
    "CL_DEVICE_NOT_FOUND",                //-1
    "CL_DEVICE_NOT_AVAILABLE",            //-2
    "CL_COMPILER_NOT_AVAILABLE",          //-3
    "CL_MEM_OBJECT_ALLOCATION_FAILURE",   //-4
    "CL_OUT_OF_RESOURCES",                //-5
    "CL_OUT_OF_HOST_MEMORY",              //-6
    "CL_PROFILING_INFO_NOT_AVAILABLE",    //-7
    "CL_MEM_COPY_OVERLAP",                //-8
    "CL_IMAGE_FORMAT_MISMATCH",           //-9
    "CL_IMAGE_FORMAT_NOT_SUPPORTED",      //-10
    "CL_BUILD_PROGRAM_FAILURE",           //-11
    "CL_MAP_FAILURE",                     //-12
    "",                                   //-13
    "",                                   //-14
    "",                                   //-15
    "",                                   //-16
    "",                                   //-17
    "",                                   //-18
    "",                                   //-19
    "",                                   //-20
    "",                                   //-21
    "",                                   //-22
    "",                                   //-23
    "",                                   //-24
    "",                                   //-25
    "",                                   //-26
    "",                                   //-27
    "",                                   //-28
    "",                                   //-29
    "CL_INVALID_VALUE",                   //-30
    "CL_INVALID_DEVICE_TYPE",             //-31
    "CL_INVALID_PLATFORM",                //-32
    "CL_INVALID_DEVICE",                  //-33
    "CL_INVALID_CONTEXT",                 //-34
    "CL_INVALID_QUEUE_PROPERTIES",        //-35
    "CL_INVALID_COMMAND_QUEUE",           //-36
    "CL_INVALID_HOST_PTR",                //-37
    "CL_INVALID_MEM_OBJECT",              //-38
    "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR", //-39
    "CL_INVALID_IMAGE_SIZE",              //-40
    "CL_INVALID_SAMPLER",                 //-41
    "CL_INVALID_BINARY",                  //-42
    "CL_INVALID_BUILD_OPTIONS",           //-43
    "CL_INVALID_PROGRAM",                 //-44
    "CL_INVALID_PROGRAM_EXECUTABLE",      //-45
    "CL_INVALID_KERNEL_NAME",             //-46
    "CL_INVALID_KERNEL_DEFINITION",       //-47
    "CL_INVALID_KERNEL",                  //-48
    "CL_INVALID_ARG_INDEX",               //-49
    "CL_INVALID_ARG_VALUE",               //-50
    "CL_INVALID_ARG_SIZE",                //-51
    "CL_INVALID_KERNEL_ARGS",             //-52
    "CL_INVALID_WORK_DIMENSION ",         //-53
    "CL_INVALID_WORK_GROUP_SIZE",         //-54
    "CL_INVALID_WORK_ITEM_SIZE",          //-55
    "CL_INVALID_GLOBAL_OFFSET",           //-56
    "CL_INVALID_EVENT_WAIT_LIST",         //-57
    "CL_INVALID_EVENT",                   //-58
    "CL_INVALID_OPERATION",               //-59
    "CL_INVALID_GL_OBJECT",               //-60
    "CL_INVALID_BUFFER_SIZE",             //-61
    "CL_INVALID_MIP_LEVEL",               //-62
    "CL_INVALID_GLOBAL_WORK_SIZE"};       //-63

//! OpenCl Error checker
/*!
Checks for error code as per cl_int returned by OpenCl
\param status Error value as cl_int
\param msg User provided error message
\return True if Error Seen, False if no error
*/
int ad_errChk(const cl_int status, const char * msg, bool exitOnErr)
{

    if(status != CL_SUCCESS) {
        printf("OpenCL Error: %d %s %s\n", status, cl_err_msg[-status], msg);

        if(exitOnErr) {
            exit(-1);
        }

        return true;
    }
    return false;
}

//! \return the next highest value such that x/y = 0
// This function that takes a positive integer 'value' and returns
// the nearest multiple of 'multiple' (used for padding columns)
unsigned int idivup(unsigned int value, unsigned int multiple) {

   unsigned int remainder = value % multiple;

   // Make the value a multiple of multiple
   if(remainder != 0) {
      value += (multiple-remainder);
   }

   return value;
}


//-------------------------------------------------------
//          Synchronization functions
//-------------------------------------------------------

/*!
    Wait till all pending commands in queue are finished
*/
void ad_sync(cl_command_queue commandQueue)
{
    clFinish(commandQueue);
}

