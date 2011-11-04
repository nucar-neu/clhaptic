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

void * analysis_device::mapBuffer(cl_mem mem, size_t mem_size, cl_mem_flags flags)
{
    cl_int status;
    void *ptr;

	/*
	 * 	static int eventCnt = 0;
		cl_event* eventPtr = NULL, event;

		if(eventsEnabled) {
			eventPtr = &event;
		}
	*/
    //! Blocking map operation used, no offset
    ptr = (void *)clEnqueueMapBuffer(queue,
								mem, CL_TRUE, flags,
								 0, mem_size, 0, NULL,
								 NULL,
								 //eventPtr,
								 &status);

    ad_errChk(status, "Error mapping a buffer", true);

    //if(eventsEnabled) {
    //    char* eventStr = catStringWithInt("MapBuffer", eventCnt++);
    //    events->add(*eventPtr, eventStr);
    //}

    return ptr;
}


void result_buffer::allocate_buffer(size_t size, cl_context ctx)
{
	mem_size = size;
	buffer=  ad_allocBufferPinned(mem_size,ctx);

}

void result_buffer::allocate_image(size_t size, cl_context ctx)
{
	mem_size = size;
	buffer=  ad_allocBufferPinned(mem_size,ctx);

}

result_buffer::result_buffer()
{
	mem_size = UNKNOWNSIZE;
}

/**
 * Default constructor.
 * Sets waitlists
 */
analysis_device::analysis_device()
{
	//! By default, no waitlist used
 	len_analysis_waitlist = 0;
	analysis_waitlist = NULL;
	n_analysis_kernels = 0;
	device_state = ENABLED;
	/**
	 * Profiler initialization cannot be done in the constructor
	 * because you need the device and context and other such details.\n
	 * The profiler needs a valid setup since it queries the clocks on
	 * initialization
	 */
}

analysis_device::~analysis_device()
{

	// Shutdown fissions tuff
	free(topo);
	delete profiler;
}

cl_kernel analysis_device::getKernel(int k)
{
	//! Bound check
 	if(k < n_analysis_kernels)
		return kernel_vec.at(k)->kernel;
	else
	{
		printf("Invalid Kernel Requested\n");
		exit(-1);

	}
}

void analysis_device::set_device_state(bool instate)
{
	device_state = instate;
}
bool analysis_device::get_device_state()
{
	return device_state;
}


/**
 *
 * @param mem Host memory
 * @param buff Buffer on analysis device
 * @param mem_size Memory size
 */
void analysis_device::copyHostToAd(cl_mem buff,void * mem,  size_t mem_size)
{
	cl_int status ;
	status = clEnqueueWriteBuffer(queue,buff,1,0,mem_size,mem,0,NULL,NULL);
	ad_sync(queue);
	ad_errChk(status, "copyHostToAd Error");
}

/**
 *
 * @return Context for derived classes
 */
cl_context analysis_device::getContext()
{
	return context;
}


void analysis_device::configure_analysis_subdevice_cpu(char * name )
{

	topo = new fission_topology;

	setup_fission(topo);

	//! Topo now has populated with the analysis device
	queue = topo->subQueue[0];

	//queue = topo->();
	context = topo->subContext;
	device = topo->subDevices[0];

	// Initialize the profiler for the analysis device
	char prof_name[]= "analysis_prof";
	profiler = new EventList(context,queue,device,1,prof_name);

}


void analysis_device::sync()
{
	cl_int status;
	status = clFinish(queue);
	ad_errChk(status,"Error Waiting for Analysis Device to finish");
}


//! For the case where you may want to preallocate a number of kernels
/**
 *
 * @param k
 */
void analysis_device::alloc_kernel_mem(int k)
{
	printf("Resizing Kernel Vector - Not Good\n");
	n_analysis_kernels = k;
	//! Old api was to have a array of analysis_kernels instead of a vector
	//!analysis_kernels = ( cl_kernel *)malloc(k*sizeof(cl_kernel));
	kernel_vec.resize(k);

}

char * analysis_device::generate_kernel_path(char * filename)
{
	printf("Unimplemented generate_kernel_path \n");
	exit(-1);

}

kernel_object analysis_device::alloc_kernel_object()
{
	return new _kernel_object;
}

void analysis_device::build_analysis_kernel(char * filename, char * kernel_name,int pos)
{
 	topo->cl_CompileProgramRootDevices(filename,NULL,0);
 	topo->cl_CompileProgramSubDevice(filename,NULL,0);
	//TODO Fix this constant allocation
 	analysis_program =  topo->sub_program[0];

 	cl_int status;

 	//!analysis_kernels[pos] = clCreateKernel(analysis_program,kernel_name,&status);
 	//!New API for kernel object, wrap up all the things needed to launch a kernel
 	//!Dont add a cl_command_queue here because we dont know what device stuff gets thrown on

 	kernel_object k = alloc_kernel_object();
 	k->dim_globalws = 2;
 	k->dim_localws = 2;
 	k->name = kernel_name;
 	k->kernel = clCreateKernel(analysis_program,kernel_name,&status);
 	cl_errChk(status, "Creating Analysis Kernel",EXITERROR);
 	kernel_vec.push_back(k);
 	n_analysis_kernels ++;


}


void analysis_device::configure_analysis_rootdevice()
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
	queue = topo->rootQueue[0];
	//queue = topo->();
	context = topo->root_context ;
	device = topo->root_device;

	// Initialize the profiler for the analysis device
	profiler = new EventList(context,queue,device,1);

	printf("Analysis Device Set Up Successfully\n");
}

//! Either create a new profiler object or use the input EventList provided
void analysis_device::init_app_profiler(EventList * profiler_locn)
{
	if(profiler_locn == NULL)
	{
		printf("Init new App profiler");
		app_profiler = new EventList(context,queue,device,TRUE);
	}
	else
	{
		printf("Init App profiler with %s \n",profiler_locn->get_profiler_name());
		app_profiler = profiler_locn;
	}
}
/**
 * @param Kernel number to run, no argument means all kernels in vector are run
 */
void analysis_device::inject_analysis(int kernel_to_inject   )
{
	cl_int status;

	//profiler->samplePhaseChange();
	//printf("Number of kernels %ld\n", kernel_vec.size());
	//!TODO Multiple kernels could be enqueued

	if(kernel_to_inject == UNKNOWN)
	{
		for(int i = 0; i< kernel_vec.size() ; i++)
		{

			cl_event analysis_event;
			status = clEnqueueNDRangeKernel(queue,
						kernel_vec[i]->kernel,
						kernel_vec[i]->dim_globalws,
						0,kernel_vec[i]->globalws,kernel_vec[i]->localws,
						len_analysis_waitlist,analysis_waitlist,
						&analysis_event);
			cl_errChk(status,"Enq inj analysis", EXITERROR);
			profiler->add(analysis_event);

		}
	}
	else
	{
		cl_event analysis_event;
		// Run kernel from vector with bound checking
		status = clEnqueueNDRangeKernel(queue,
					kernel_vec.at(kernel_to_inject)->kernel,
					kernel_vec.at(kernel_to_inject)->dim_globalws,
					0,
					kernel_vec.at(kernel_to_inject)->globalws,
					kernel_vec.at(kernel_to_inject)->localws,
					len_analysis_waitlist,analysis_waitlist,
					&analysis_event);
		cl_errChk(status,"Enq inj analysis", EXITERROR);
		profiler->add(analysis_event);

	}

}