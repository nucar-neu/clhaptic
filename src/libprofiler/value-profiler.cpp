
#include <CL/cl.h>
#include "opencl_utils.h"
#include "value-profiler.h"

void value_profiler::check_value_on_host(ad_rule rule)
{
	cl_int status;
	int mem_size;
	void * ptr = clEnqueueMapBuffer(access_queue,
							buff,CL_TRUE,NULL,offset,mem_size,
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
