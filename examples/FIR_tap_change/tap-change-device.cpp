#include <CL/cl.h>
#include "analysis-devices.h"
#include "tap-change-device.h"

tap_change_device::tap_change_device()
{
	change_interval = UNKNOWN;

}


void tap_change_device::add_phase(int ip_phase_id)
{
	app_profiler->simple_enqueue_phase(ip_phase_id);
	if( (app_profiler->get_latest_phase_id()) % change_interval == 0)
	{
		printf("\t\t\tEnable Device\n");
		set_device_state(ENABLED);
	}
	else
	{
		printf("\t\t\tDisable Device\n");
		set_device_state(DISABLED);
	}
}

//! Setup device
void tap_change_device::init_tap_change_device(int ip_n_taps, int ip_n_iterations)
{
	num_taps = ip_n_taps;
	num_iterations = ip_n_iterations;
	change_interval = 10;
	configure_analysis_device_gpu(getContext());

	cl_int status;

	coeff_buff = clCreateBuffer(getContext(),CL_MEM_READ_WRITE,num_taps*sizeof(float),NULL,&status);
	ad_errChk(status,"error declaring buffers");

}

//! Configure the analysis kernel.
//! At this stage the kernel should be allocated and compiled
//! \param p_img Present Image
//! \param p_img Next Image
void tap_change_device::configure_analysis_kernel()
{
	//	printf("Setting Arguments and Config Analysis Kernel\n");

	kernel_vec.at(0)->dim_globalws = 1;
	kernel_vec.at(0)->dim_localws = 1;
	kernel_vec.at(0)->localws[0] = 64;
	kernel_vec.at(0)->globalws[0] = num_taps;

	//kernel_vec.at(0)->localmemsize = (sizeof(float)*(kernel_vec.at(0)->localws[0])*(kernel_vec.at(0)->localws[1]));

 	ad_setKernelArg(getKernel(0), 0,sizeof(cl_mem),(void *)&coeff_buff);
	ad_setKernelArg(getKernel(0), 1,sizeof(cl_int), (void *)&num_iterations);
	ad_setKernelArg(getKernel(0), 2,sizeof(cl_int), (void *)&num_taps);


}
