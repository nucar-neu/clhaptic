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

class value_profiler
{

private:

	std::vector<result_buffer> locn;
	std::vector<value_profiler_config> config_locn;

	//! Location of memory
	cl_mem buff;
	int offset;

	cl_context ctx;
	cl_command_queue access_queue;

	inline bool apply_rule_exact(ad_rule ip_rule);
	inline bool apply_rule_less_than(ad_rule ip_rule);
	inline bool apply_rule_more_than(ad_rule ip_rule);

public:

	//! Assign context and queue
	void init(cl_command_queue, cl_context);

	void set_buffer(cl_mem ip_buff, int ip_offset);
	void check_value_on_host(ad_rule );
	void check_value_on_device();
	void record_result_on_host();
	void record_result_on_device();

	bool test_rule(ad_rule ip_rule);
};

#endif //  __VALUE_PROFILER_


