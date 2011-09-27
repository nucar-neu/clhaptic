#include <CL/cl.h>

#include "../profiler/eventlist.h"

 #include "analysis-routines.h"

//enum image_similarity;

compare_images::compare_images()
{
	printf("Default Base Constructor \n");
}

void compare_images::assign_buffers(float * prev, float * next)
{
	//! Uses the cl_map calls to map the pointers passed to the
	//! buffer objects
}

bool compare_images::set_pipeline_state()
{
	return ENABLED;
}
//! Configure the analysis kernel
//! \param p_img Present Image
//! \param p_img Next Image
void compare_images::configure_analysis_kernel( cl_mem p_img, cl_mem n_img, int W, int H )
{

	alloc_kernel_mem(2);
	set_analysis_kernel("analysis-CLSource/compare_images.cl", "compare",0);
	set_analysis_kernel("analysis-CLSource/compare_images.cl", "average",1);

	//! If present_image and next_image

	ws_dims = 2;
	localws[0] = 16; localws[1] = 16;
	globalws[0] = W; globalws[1] = H;


	ad_setKernelArg(getKernel(0), 0,sizeof(cl_mem), p_img);
	ad_setKernelArg(getKernel(0), 0,sizeof(cl_mem), n_img);
	ad_setKernelArg(getKernel(0), 0, sizeof(cl_mem), opbuff.result_buffer);

	ad_setKernelArg(getKernel(1), 0,sizeof(cl_mem), p_img);
	ad_setKernelArg(getKernel(1), 0,sizeof(cl_mem), n_img);
	ad_setKernelArg(getKernel(1), 0, sizeof(cl_mem), opbuff.result_buffer);

//	cl_mapBuffer();


}


//! Input- Feature set
//! Output- Sorted set (sorted as per all Xcord followed by all Ycoord)
/*
int sort_features()
{


}

int orntn_check()
{
	cl_mem buff1;
	cl_mem buff2;
	cl_kernel ortn_compare;
	//! Get Feature Sets
	cl_setKernelArg()

	//! Get Feature Set2


}
*/

