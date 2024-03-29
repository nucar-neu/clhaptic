/*
#ifndef __OPENCL_VERSION__

#define __kernel
#define __global
#define get_global_id

#endif
*/

__kernel void sum_op_kernel(
		__global float * input_tap,
		int n_tap, int n_iterations)
{

	float old_tap = input_tap[get_global_id(0)];
	float new_tap = 0;
	for(int k=0; k < n_iterations; k++)
	{
		new_tap = new_tap + old_tap*(1.0f/(100.0f*100.0f*100.0f));
	}
	input_tap[get_global_id(0)] = new_tap;
}
		
