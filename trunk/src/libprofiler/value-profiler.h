#ifndef __VALUE_PROFILER_
#define __VALUE_PROFILER_

#include <CL/cl.h>
#include <vector>

#include "opencl_utils.h"
#include "ad_rule_vec.h"

#define RESULT_ON_DEVICE	9001
#define RESULT_ON_HOST 		9002
#define CHECK_ON_DEVICE 	9003
#define CHECK_ON_HOST 		9004

/**
 * A method for managing cl_mem type analysis_results
 */
class result_buffer
{


public:
	float variation;
	int offset;
	size_t mem_size;
	result_buffer();
	void allocate_image(size_t size, cl_context ctx);
	void allocate_buffer(size_t size, cl_context ctx);
	cl_mem buffer;
};


struct value_profiler_config
{
	int read_method;
	int write_method;
};

//! The problem with the present methodology is simple type information which is missing.
class value_profiler
{

private:

	cl_kernel test_kernel;
	bool profiler_state;
	std::vector<result_buffer> locn;
	std::vector<value_profiler_config> config_locn;

	//! Location of memory. This has been removed because all buffers should be checked via their respective rule
	//cl_mem buff;
	//int offset;

	inline bool apply_rule_exact(ad_rule ip_rule);
	inline bool apply_rule_less_than(ad_rule ip_rule);
	inline bool apply_rule_more_than(ad_rule ip_rule);

public:

	cl_context ctx;
	cl_device_id access_device;
	cl_command_queue access_queue;

	value_profiler();
	//! Assign context and queue and device if necessary
	void init(cl_command_queue, cl_context,cl_device_id = NULL);
	//! An alternate non rule method to set a buffer to profile
	void set_buffer(cl_mem ip_buff, int ip_offset);
	void check_value_on_host(ad_rule );
	void check_value_on_device(ad_rule);
	void record_result_on_host();
	void record_result_on_device();

	bool test_rule(ad_rule ip_rule);
};

#endif //  __VALUE_PROFILER_


