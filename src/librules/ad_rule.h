#ifndef __ANALYSIS_RULE__
#define __ANALYSIS_RULE__

#include <CL/cl.h>
#include <vector>

#include "opencl_utils.h"
#include "rule_type.h"

//! Define a rule that is checked by an analysis-device object.
//! The OpenCL device specific things like cl_context and a cl_command_queue are passed to the object
class ad_rule
{
private:

	//! The type of test that needs to be done.
	rule_type type;
	//! OpenCL Buffer. The location of the non architectural event
	cl_mem target_buffer;
	float target_value;
	void * target_ptr;
	int buffer_offset;

	//! Added for checking more than one value
	size_t mem_size;

	//! Private functions added since high level code, may not know exact rule
	bool apply_rule_exact(cl_context , cl_command_queue );
	bool apply_rule_less_than(cl_context , cl_command_queue );
	bool apply_rule_more_than(cl_context , cl_command_queue );
public:

	ad_rule();
	cl_int add();
	cl_int add(rule_type, cl_mem, float val);
	//! Interface to call all the apply_ functions
	void print_rule_details();
	bool test_rule(cl_context ctx, cl_command_queue queue);

};


#endif
