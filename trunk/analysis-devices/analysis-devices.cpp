#include <CL/cl_ext.h>
#include <CL/cl.h>

#include <stdio.h>
#include "analysis-devices-utils.h"
#include "fission_topology.h"
#include "fissionutils.h"
#include "analysis-devices.h"

//! This define makes the utility functions point to their ad_ counterparts.
//! This is done since SURF and the Palantir both use the same set of utility functions
#define cl_errChk ad_errChk

void analysis_results::allocate_buffer(size_t mem_size, cl_context ctx)
{
	ad_allocBufferPinned(mem_size,ctx);

}

analysis_device::analysis_device()
{
	//! By default, no waitlist used
	ws_dims = 2;
	len_analysis_waitlist = 0;
	analysis_waitlist = NULL;
	//profiler(context,queue,device,1);
}

analysis_device::~analysis_device()
{
	free(analysis_kernels);
	// Shutdown fissions tuff
	free(topo);
	delete profiler;
}

cl_kernel analysis_device::getKernel(int k)
{
	//! Bound check
	if(k < n_analysis_kernels)
		return analysis_kernels[k];
	else
	{
		printf("Invalid Kernel Requested\n");
		exit(-1);

	}
}

void analysis_device::alloc_kernel_mem(int k)
{
	n_analysis_kernels = k;
	analysis_kernels = ( cl_kernel *)malloc(k*sizeof(cl_kernel));
	if(analysis_kernels == NULL)
		printf("malloc error");
}

char * analysis_device::generate_kernel_path(char * filename)
{
	printf("Unimplemented generate_kernel_path \n");
	exit(-1);

}

void analysis_device::set_analysis_kernel(char * filename, char * kernel_name,int pos)
{
 	topo->cl_CompileProgramRootDevices(filename,NULL,0);
	//TODO Fix this constant allocation
 	analysis_program =  topo->root_program[0];

 	cl_int status;
 	analysis_kernels[pos] = clCreateKernel(analysis_program,kernel_name,&status);

	ad_errChk(status, "Creating Analysis Kernel",EXITERROR);

}

void analysis_device::configure_analysis_device()
{

	topo = new fission_topology;

	// Configuration Command for Device Fission
//    cl_device_partition_property_ext partitionPrty[3] =
//    {       CL_DEVICE_PARTITION_EQUALLY_EXT,
//            1,
//            CL_PROPERTIES_LIST_END_EXT
 //   };

	//setup_fission(topo,partitionPrty);

	setup_fission(topo);

	//! Topo now has populated with the analysis device

	queue = topo->return_subqueue();
	context = topo->root_context ;
	printf("Analysis Device Set Up Successfully\n");
}

void analysis_device::inject_analysis()
{
	cl_int status;
	//cl_setKernelArg(kernel,);

	cl_event analysis_event;
	//!TODO Multiple kernels could be enqueued
	for(int i = 0; i<n_analysis_kernels; i++)
	{
		status = clEnqueueNDRangeKernel(queue,analysis_kernels[i],
					ws_dims,0,globalws,localws,
					len_analysis_waitlist,analysis_waitlist,
					&analysis_event);
		cl_errChk(status,"Enq inj analysis", EXITERROR);
	}
	profiler->add(analysis_event);
}
