#include <stdio.h>
#include <CL/cl.h>
#include "analysis-devices-utils.h"
#include "eventtypes.h"
#include <cmath>
#include <iostream>
#include <ctime>


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

