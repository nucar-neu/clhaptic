#include "stdio.h"
#include "opencl_utils.h"
#include "ad_rule.h"
#include "rule_type.h"


bool ad_rule::test_rule(cl_context ctx, cl_command_queue queue)
{
	if(type == VALUE_EXACT)
	{
		if(apply_rule_exact(ctx,queue) )
			return RULE_SUCCESS;
		else
			return RULE_FAILURE;
	}
	if(type == VALUE_LESS_THAN)
	{
		if(apply_rule_less_than(ctx,queue))
			return RULE_SUCCESS;
		else
			return RULE_FAILURE;
	}

	if(type == VALUE_MORE_THAN)
	{
		if(apply_rule_more_than(ctx,queue))
			return RULE_SUCCESS;
		else
			return RULE_FAILURE;
	}
	if(type == UNDEFINED_RULE)
	{
		printf("rule not defined yet");
		exit(-1);
	}
}

void print_rule_details()
{
	//TODO
	printf("Pretty printing TODO");

}

bool ad_rule::apply_rule_less_than(cl_context ctx, cl_command_queue queue)
{
	cl_int status;

	target_ptr = clEnqueueMapBuffer(queue,target_buffer,
							CL_TRUE, CL_MEM_READ_ONLY,
							0,mem_size,0,
							NULL,NULL,&status);
	ad_errChk(status,"error mapping buffer");

}

bool ad_rule::apply_rule_more_than(cl_context ctx, cl_command_queue queue)
{
	cl_int status;
	target_ptr = clEnqueueMapBuffer(queue,target_buffer,
							CL_TRUE, CL_MEM_READ_ONLY,
							0,mem_size,0,
							NULL,NULL,&status);
	ad_errChk(status,"error mapping buffer");

}


bool ad_rule::apply_rule_exact(cl_context ctx, cl_command_queue queue)
{
	cl_int status;

	target_ptr = clEnqueueMapBuffer(queue,target_buffer,
							CL_TRUE, CL_MEM_READ_ONLY,
							0,mem_size,0,
							NULL,NULL,&status);

	ad_errChk(status,"error mapping buffer");
}


ad_rule::ad_rule()
{
	type = UNDEFINED_RULE;
}


cl_int ad_rule::add()
{

}

cl_int ad_rule::add(rule_type t, cl_mem ip_buff, float ip_value)
{
	target_buffer= ip_buff ;
	type = t;
	target_value = ip_value;
	mem_size = sizeof(float);
}

