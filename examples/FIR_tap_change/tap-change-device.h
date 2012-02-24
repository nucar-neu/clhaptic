#include "analysis-devices.h"
#include "opencl_utils.h"

class tap_change_device : public analysis_device
{
public:
	int change_interval;
	int num_taps;

	//! Amount of time taken by tap_change_device kernels
	int num_iterations;
	cl_mem coeff_buff;

	void add_phase(int ip_phase_id);
	void init_tap_change_device(int , int);
	tap_change_device();
	void configure_analysis_kernel();

};
