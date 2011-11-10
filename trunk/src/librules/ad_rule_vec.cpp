#include <CL/cl.h>
#include "ad_rule_vec.h"

void ad_rule_vec::add_rule(ad_rule ip)
{
	if(verbose_logging)
		ip.print_rule_details();

	rule_list.push_back(ip);
}


//! For now, all rules are always active.
//!	Return the number of active rules
int ad_rule_vec::active_rule_count()
{
	return rule_list.size();
}

void ad_rule_vec::apply_rule(cl_context ctx, cl_command_queue queue, int i)
{
	rule_list.at(i).test_rule(ctx,queue);

}