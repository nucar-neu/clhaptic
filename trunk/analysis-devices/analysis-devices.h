
#include <CL/cl.h>
#include "analysis-devices-utils.h"
#include "fissionutils.h"
#include "../profiler/eventlist.h"

#ifndef __ANALYSIS_DEVICE_
#define __ANALYSIS_DEVICE_

//! A kernel object containing all the necessary parameters to launch a kernel.
//! Dont add a cl_command_queue here because we dont know what device kernel gets thrown on
struct _kernel_object
{
	cl_kernel kernel;
	//! _kernel_object::localws and globalws hardwired to 3. Max dim of OpenCL kernels
	size_t dim_localws;
	size_t dim_globalws;
	//!_kernel_object::localws and _kernel_object::globalws are hard wired to 3. Max dim of OpenCL kernels
	size_t localws[3];
	size_t globalws[3];
	char * name;
	int n_args;

	size_t localmemsize;
	//! Waitlist for kernel. UNUSED for now
	cl_event * waitlist;

	//! Num of elements in waitlist UNUSED for now
	int len_waitlist;
};

//! Typedef in a similar manner as things like cl_mem
typedef _kernel_object * kernel_object;

/**
 * A method for managing cl_mem type analysis_results
 */
class result_buffer
{

public:
	size_t mem_size;
	result_buffer();
	void allocate_image(size_t size, cl_context ctx);
	void allocate_buffer(size_t size, cl_context ctx);
	cl_mem buffer;
};

/**
 * A general analysis device base class.
 * Different analysis devices can be derived from this
 * class with their own kernels and so on.
 * This class includes all the architectural state needed to define a device \n
 * Derived classes only need to define the kernels and the buffers.
**/
class analysis_device
{

private:

	//! This could map to any OpenCL device or subdevice
	cl_command_queue queue;
	//! Used OpenCL context. This should be the same context as the
	cl_context context;
	//! Device ID of the analysis device
	cl_device_id device;
	cl_program analysis_program;


	//! Analysis Device is a Fission Topology
	fission_topology * topo;
	//! Kernel declaration made protected.
	//! Since specific inherited case needs to set args

	int n_analysis_kernels;

protected:

	std::vector<kernel_object> kernel_vec;

	//! Derived classes need to configure these
	cl_event * analysis_waitlist;
	cl_uint len_analysis_waitlist;

	//! Add python script's parameters
	int frequency;

public:
	void copyHostToAd( cl_mem buff, void * mem, size_t mem_size);
	//! Return the kernel object
	cl_kernel getKernel(int k);

	~analysis_device();
	//! Profiler for analysis device.
	//! Handles timing and the insertion of kernels
	EventList * profiler;

	result_buffer result;

	analysis_device();
	void alloc_kernel_mem(int k);
	kernel_object alloc_kernel_object();
	//! Compile kernels for device
	void build_analysis_kernel(char * filename, char * kernel_name, int pos);
	//! Set up Fission, create root context and subqueues
	void configure_analysis_device();

	//! Will be called by function defined in the derived class
	void inject_analysis();

	char * generate_kernel_path(char * filename);
	cl_context getContext();

};

#endif //__ANALYSIS_DEVICE_