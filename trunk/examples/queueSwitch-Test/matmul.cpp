#include "matmul.h"
#include "stdio.h"
#include "math.h"

void matmul::init_data(int mat_width, int N_problems)
{
    W = mat_width;
    N = N_problems;

    A = (float *)malloc(sizeof(float)*N*W*W);
    B = (float *)malloc(sizeof(float)*N*W*W);
    C = (float *)malloc(sizeof(float)*N*W*W);
    ref = (float *)malloc(sizeof(float)*W*W*N);

    for(int i=0;i< N*W*W; i++)
    {
        A[i] = float(rand())/float(RAND_MAX);
        B[i] = float(rand())/float(RAND_MAX);
    }

}




void matmul::init_matmul(fission_topology * topo, bool ip_profiling_flag)
{

	profiling_flag = ip_profiling_flag;

	if(profiling_flag == ENABLED){
		matmul_profiler = new EventList(
							topo->root_context,
							topo->rootQueue[0],
							topo->devices[0],TRUE,
							"matmul_profiler");

		matmul_profiler->setProfilingStatus(profiling_flag);
	}
    d_A = (cl_mem *)malloc(sizeof(cl_mem)*topo->numRootDevices);
    d_B = (cl_mem *)malloc(sizeof(cl_mem)*topo->numRootDevices);
    d_C = (cl_mem *)malloc(sizeof(cl_mem)*topo->numRootDevices);

    topo->cl_CompileProgramRootDevices("matrixMul.cl",0,0);


    //! To fix: No of kernels needed == No of sub devices
    multiplicationKernel = (cl_kernel *)malloc(sizeof(cl_kernel)*(topo->numRootDevices));
    cl_int status;

    for(int i=0;i < topo->numRootDevices; i++)
    {
        multiplicationKernel[i]=clCreateKernel(topo->root_program[i],"matrixMul",&status);
        cl_errChk(status,"error creating kernel");

        d_A[i] = clCreateBuffer(topo->root_context,
                            CL_MEM_READ_ONLY,
                            W*W* sizeof(float) , NULL,NULL);


        // create OpenCL buffer on device that will be initiatlize from the host memory on first use
        // on device
        d_B[i] = clCreateBuffer(topo->root_context,
                            CL_MEM_READ_ONLY,
                            W*W* sizeof(float) , NULL,NULL);

        d_C[i] = clCreateBuffer(topo->root_context,
                            CL_MEM_READ_ONLY,
                            W*W* sizeof(float) , NULL,NULL);

        // set the args values
        clSetKernelArg(multiplicationKernel[i], 0, sizeof(cl_mem), (void *) &d_C[i]);
        clSetKernelArg(multiplicationKernel[i], 1, sizeof(cl_mem), (void *) &d_A[i]);
        clSetKernelArg(multiplicationKernel[i], 2, sizeof(cl_mem), (void *) &d_B[i]);
        clSetKernelArg(multiplicationKernel[i], 3, sizeof(float) * BLOCK_SIZE *BLOCK_SIZE, 0 );
        clSetKernelArg(multiplicationKernel[i], 4, sizeof(float) * BLOCK_SIZE *BLOCK_SIZE, 0 );
        clSetKernelArg(multiplicationKernel[i], 5, sizeof(cl_int), (void *) &W);
        clSetKernelArg(multiplicationKernel[i], 6, sizeof(cl_int), (void *) &W);

    }
    printf("Finished Setup\n");
}

//! Limit Fission specific things to here
void matmul::computekernel(int problemid, fission_topology * topo, cl_command_queue target_queue)
{

	int i = problemid;
	size_t localWorkSize[2]={BLOCK_SIZE,BLOCK_SIZE};
    size_t globalWorkSize[2] = {W,W};
    cl_int status = CL_SUCCESS;



    // Copy only assigned rows from host to device
    float * h_A = &A[W*W*i];
    float * h_B = &B[W*W*i];
    float * h_C = &C[W*W*i];


    //printf("starting locn %d \t %d\n",W*W*i,topo->numSubDevices);
    /* Write data to buffer */
    cl_event e0;
    status |= clEnqueueWriteBuffer(target_queue,
                              d_A[0], CL_FALSE,
                              0, sizeof(cl_float) * W * W,
                              &A[W*W*i], 0, NULL,
    //                              NULL);
                      &e0);
    if(profiling_flag == ENABLED)
    	matmul_profiler->add(e0);
    cl_errChk(status, "Error enq write d_A");


    /* Write data to buffer */
    cl_event  e1 ;
    status |= clEnqueueWriteBuffer(target_queue,
                              d_B[0],CL_FALSE,
                              0, sizeof(cl_float) * W * W,
                              &B[W*W*i], 0, NULL,
    //                                  NULL);
                              &e1);
    if(profiling_flag == ENABLED)
    	matmul_profiler->add(e1);
    cl_errChk(status, "Error enq write d_B");

    cl_event  e2 ;
    status |= clEnqueueNDRangeKernel(target_queue,
                                multiplicationKernel[0], 2,
                                0, globalWorkSize, localWorkSize,
                                0, NULL,
    //                                NULL);
                                &e2);
    if(profiling_flag == ENABLED)
    	matmul_profiler->add(e2);
    cl_errChk(status, "Error running kernel");


    // Non-blocking copy of result from device to host
    cl_event  e3;
    status |= clEnqueueReadBuffer(target_queue,
                              d_C[0], CL_FALSE,
                              //CL_TRUE,
                              0, W*W*sizeof(float),
                              &C[W*W*i],
                              0, NULL,
    //                            NULL);
                              &e3);
    if(profiling_flag == ENABLED)
    	matmul_profiler->add(e3);
    cl_errChk(status, "Error enq read d_C");
}


void matmul::matmul_ocl(fission_topology * topo)
{



    //int problems_per_sub_device = ceil(float(N)/float(topo->numSubDevices));
    //printf("%d Problems per subdevice \n",problems_per_sub_device);
    for(unsigned int k = 0; k < N; k++)
    {

        computekernel(k,topo,topo->rootQueue[0]);
        //clFinish(target_queue);
    }
    //for(int i=0; i< (topo->numSubDevices);i++)
        //clFlush(topo->subQueue[i]);

}

matmul::~matmul()
{

    for(int i=0 ; i<N;i++)
    {
        clReleaseMemObject(d_A[i]);
        clReleaseMemObject(d_B[i]);
        clReleaseMemObject(d_C[i]);
    }

    free(d_A);
    free(d_B);
    free(d_C);
    free(A);
    free(B);
    free(C);

}

void matmul::baseline( int problem_id
//            float* C, const float* A, const float* B,
//            unsigned int hA, unsigned int wA, unsigned int wB
            )
{


    float * h_A = &A[W*W*problem_id];
    float * h_B = &B[W*W*problem_id];
    float * h_C = &ref[W*W*problem_id];


    for (unsigned int i = 0; i < W; ++i)
    {

        for (unsigned int j = 0; j < W; ++j)
        {
            float sum = 0;
            for (unsigned int k = 0; k < W; ++k)
            {
                float a = h_A[i * W + k];
                float b = h_B[k * W + j];
                sum += a * b;
            }
            h_C[i * W + j] = (float)sum;

        }
    }
}


void matmul::baseline_compare( int problem_id)
{


    for(int i=0; i<(W*W);i++)
    {

        if( (ref[i+problem_id*W*W] - C[i+problem_id*W*W] ) > 1e-6)
        {
            printf("%d\t %f\t%f\n",i,ref[i+problem_id*W*W],C[i+problem_id*W*W]);
            printf("Error");
            // exit(1);
        }
    }

}
