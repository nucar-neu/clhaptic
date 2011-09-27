
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
	//!localws and global ws hardwired to 3. Max dim of OpenCL kernels
	size_t dim_localws;
	size_t dim_globalws;
	//!localws and global ws hardwired to 3. Max dim of OpenCL kernels
	size_t localws[3];
	size_t globalws[3];
	char * name;
	int n_args;
};

typedef _kernel_object * kernel_object;

class analysis_results
{

public:
	void allocate_buffer(size_t mem_size, cl_context ctx);
	cl_mem result_buffer;
};


class analysis_device
{

private:

	//! This could map to any OpenCL device or subdevice
	cl_command_queue queue;
	cl_context context;
	//! Device ID of the analysis device
	cl_device_id device;
	cl_program analysis_program;


	//! Analysis Device is a Fission Topology
	fission_topology * topo;
	//! Kernel declaration made protected.
	//! Since specific inherited case needs to set args
	cl_kernel * analysis_kernels;
	int n_analysis_kernels;
	std::vector<kernel_object> kernel_vec;

protected:

	//! Derived classes need to configure these
	cl_event * analysis_waitlist;
	cl_uint len_analysis_waitlist;

	//! Local and global work group sizes
	size_t localws[3];
	size_t globalws[3];
	int ws_dims;


	//! Add python script's parameters
	int frequency;


public:

	cl_kernel getKernel(int k);

	~analysis_device();

	EventList * profiler;

	analysis_results result;

	analysis_device();
	void alloc_kernel_mem(int k);
	kernel_object alloc_kernel_object();
	//! Compile kernel for device
	void set_analysis_kernel(char * filename, char * kernel_name, int pos);
	//! Set up Fission, create root context and subqueues
	void configure_analysis_device();

	//! Will be called by function defined in the derived class
	void inject_analysis();

	char * generate_kernel_path(char * filename);

};

#endif //__ANALYSIS_DEVICE_
