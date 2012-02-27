#include "analysis-devices.h"
#include "opencl_utils.h"
#include "ad_rule_vec.h"

class tap_change_device : public analysis_device
{
public:
	float threshold_value ;
	int change_interval;
	int num_taps;

	//! Amount of time taken by tap_change_device kernels
	int num_iterations;
	cl_mem coeff_buff;

	cl_mem input_buffer;

	value_profiler * v_profiler;
	ad_rule_vec * ruledb;

	void add_phase(int ip_phase_id);
	void check_value();

	//! Set up the value checker to see if the threshold for a set of OP signals was crossed
	void init_value_checker(cl_command_queue ip_queue, cl_context ip_ctx, cl_device_id ip_device);
	//! Function to set the value.
	void set_threshold(float value , cl_mem input_buffer, int offset );
	void init_tap_change_device(int , int);
	tap_change_device();
	void configure_analysis_kernel();

};
