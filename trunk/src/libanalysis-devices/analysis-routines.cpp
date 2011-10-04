#include <CL/cl.h>
#include <eventlist.h>
#include "analysis-routines.h"

//enum image_similarity;

compare_images::compare_images()
{
	printf("Default Base Constructor \n");
}

void compare_images::init_buffers(size_t mem_size)
{

    cl_int status;
    p_img = clCreateBuffer(getContext(),
						CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,
						mem_size, NULL, &status);
    ad_errChk(status, "Error allocating pinned memory", true);
    n_img = clCreateBuffer(getContext(),
						CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,
						mem_size, NULL, &status);
	ad_errChk(status, "Error allocating pinned memory", true);

	result.allocate_buffer(mem_size,getContext());
}

/**
 * Assign data to the analysis device's buffers
 * @param prev Previous image
 * @param next Next image
 * @param mem_size Data size
 */
void compare_images::assign_buffers_copy(float * prev, float * next, size_t mem_size)
{
	//! Uses the cl_map calls to map the pointers passed to the
	//! buffer objects
 	copyHostToAd(p_img,prev,mem_size);
	copyHostToAd(n_img,next,mem_size);

	//p_img = NULL;
	//n_img = NULL;
}


bool compare_images::set_pipeline_state()
{
	return ENABLED;
}
//! Configure the analysis kernel.
//! At this stage the kernel should be allocated and compiled
//! \param p_img Present Image
//! \param p_img Next Image
void compare_images::configure_analysis_kernel( int W, int H )
{
	printf("Setting Arguments and Config Analysis Kernel\n");

	//! If present_image and next_image
	kernel_vec.at(0)->dim_globalws = 2;
	kernel_vec.at(0)->dim_localws = 2;
	kernel_vec.at(0)->localws[0] = 16;
	kernel_vec.at(0)->localws[1] = 16;
	kernel_vec.at(0)->globalws[0] = W;
	kernel_vec.at(0)->globalws[1] = H;
	kernel_vec.at(0)->localmemsize = (sizeof(float)*(kernel_vec.at(0)->localws[0])*(kernel_vec.at(0)->localws[1]));

	printf("Local mem size %d\t %d \n",W,H);
	ad_setKernelArg(getKernel(0), 0,sizeof(cl_mem), p_img);
	ad_setKernelArg(getKernel(0), 1,sizeof(cl_mem), n_img);
	ad_setKernelArg(getKernel(0), 2,sizeof(cl_mem), opbuff.buffer);
	ad_setKernelArg(getKernel(0), 3,kernel_vec.at(0)->localmemsize, NULL);
	ad_setKernelArg(getKernel(0), 4,sizeof(cl_int), (void *)&W);
	ad_setKernelArg(getKernel(0), 5,sizeof(cl_int), (void *)&H);

	//	ad_setKernelArg(getKernel(1), 0,sizeof(cl_mem), p_img);
	//	ad_setKernelArg(getKernel(1), 0,sizeof(cl_mem), n_img);
	//	ad_setKernelArg(getKernel(1), 0, sizeof(cl_mem), opbuff.result_buffer);
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

