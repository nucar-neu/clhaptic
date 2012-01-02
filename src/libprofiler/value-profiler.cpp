#include "stdio.h"
#include <CL/cl.h>

#include "opencl_utils.h"
#include "value-profiler.h"

/**
 * Important design question that needs to be answered first
 * Where should the rule database be located ?
 */
void value_profiler::check_value_on_host(ad_rule rule)
{
	cl_int status;
	int mem_size;
	void * ptr = clEnqueueMapBuffer(access_queue,
						rule.get_target_buff(),
						CL_TRUE,NULL,
						rule.get_target_offset(),mem_size,
						0,NULL,NULL,&status);
	ad_errChk(status,"Snoop value on host", TRUE);
	rule.test_rule(ctx,access_queue);


}

void value_profiler::check_value_on_device()
{

}
void value_profiler::record_result_on_host()
{

}
void value_profiler::record_result_on_device()
{

}

void value_profiler::set_buffer(cl_mem ip_buff, int ip_offset)
{
	result_buffer r;
	r.buffer = ip_buff;
	r.offset = ip_offset;
	locn.push_back(r);

}

inline bool value_profiler::apply_rule_exact(ad_rule ip)
{
	float * target_ptr;
	cl_int status;
	target_ptr = (float *)clEnqueueMapBuffer(access_queue ,ip.get_target_buff(),
							CL_TRUE, CL_MEM_READ_ONLY,
							0,ip.get_target_mem_size(),0,
							NULL,NULL,&status);
	ad_errChk(status,"error mapping buffer");
	if(float(target_ptr[0]) == ip.get_target_value())
		return RULE_SUCCESS;
	else
		return RULE_FAILURE;
}

inline bool value_profiler::apply_rule_less_than(ad_rule ip)
{

	float * target_ptr;
	cl_int status;
	target_ptr = (float *)clEnqueueMapBuffer(access_queue,ip.get_target_buff(),
							CL_TRUE, CL_MEM_READ_ONLY,
							0,ip.get_target_mem_size(),0,
							NULL,NULL,&status);
	ad_errChk(status,"error mapping buffer");
	if(float(target_ptr[0]) == ip.get_target_value())
		return RULE_SUCCESS;
	else
		return RULE_FAILURE;
}

inline bool value_profiler::apply_rule_more_than(ad_rule ip)
{
	if(profiler_state == DISABLED)
	{
		printf("WARNING: Profiler Disabled");
		return RULE_FAILURE;
	}
	else
	{
		float * target_ptr;
		cl_int status;
		target_ptr = (float *)clEnqueueMapBuffer(access_queue,ip.get_target_buff(),
								CL_TRUE, CL_MEM_READ_ONLY,
								0,ip.get_target_mem_size(),0,
								NULL,NULL,&status);
		ad_errChk(status,"error mapping buffer");
		clFinish(access_queue);
		printf("Value seen from memory %f \n", target_ptr[0]);
		//getchar();
		if(float(target_ptr[0]) > ip.get_target_value())
			return RULE_SUCCESS;
		else
			return RULE_FAILURE;
	}
}

value_profiler::value_profiler()
{
	printf("Default Constructor - Value profiler\n");
	//! Disable value_profiler by default since it is a high overhead operation
	//profiler_state = DISABLED;
	profiler_state = ENABLED;


}

void value_profiler::init(cl_command_queue ip_queue, cl_context ip_ctx)
{
	access_queue = ip_queue;
	ctx = ip_ctx;
}

bool value_profiler::test_rule(ad_rule ip_rule)
{
	if(profiler_state == ENABLED)
	{
		if(ip_rule.get_type() == VALUE_EXACT)
		{
			if(apply_rule_exact(ip_rule ) )
				return RULE_SUCCESS;
			else
				return RULE_FAILURE;
		}
		if(ip_rule.get_type()  == VALUE_LESS_THAN)
		{
			if(apply_rule_less_than(ip_rule ))
				return RULE_SUCCESS;
			else
				return RULE_FAILURE;
		}
		if(ip_rule.get_type() == VALUE_MORE_THAN)
		{
			if(apply_rule_more_than(ip_rule ))
				return RULE_SUCCESS;
			else
				return RULE_FAILURE;
		}
		if(ip_rule.get_type()  == UNDEFINED_RULE)
		{
			printf("rule not defined yet");
			exit(-1);
		}
	}
	else
	{
		printf("Warning - Value profiler not enabled");
	}
}
