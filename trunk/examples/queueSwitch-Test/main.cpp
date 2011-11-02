#include <stdio.h>


#include "eventlist.h"
#include "fissionutils.h"
#include "fission_topology.h"


#include "timer.h"

#include "matmul.h"

#include <CL/cl.h>

int main(int argc, char ** argv)
{

	printf("Queue without profiling");
    //!Setup workload
    matmul * workload_woprof;
    workload_woprof = new matmul[1];

    fission_topology * matmul_woprof = new fission_topology[1];
    setup_root_queue(matmul_woprof, FALSE);


    printf("Queue with profiling");
    //!Setup fission
    matmul * workload_wprof;
    workload_wprof = new matmul[1];

    fission_topology * matmul_wprof = new fission_topology[1];
    setup_root_queue(matmul_wprof, TRUE);

    int W_size ;
    int N_problems;

    if(argc < 3)
    {
        W_size = 512;
        N_problems = 20;
    }
    else
    {
        W_size = atoi(argv[1]);
        N_problems = atoi(argv[2]);
    }


    //! Matrix Mul Test
    workload_wprof->init_data(W_size,N_problems);
    workload_wprof->init_matmul(matmul_wprof);

    clFlush(matmul_wprof->rootQueue[0]);
    clFinish(matmul_wprof->rootQueue[0]);

    printf("\n \n With Profiling case\n \n");

    workload_wprof->matmul_ocl(matmul_wprof);

    clFlush(matmul_wprof->rootQueue[0]);
    clFinish(matmul_wprof->rootQueue[0]);

    //! Without Profiling Case - Start
    printf("\n \n WO profile case\n \n");

    workload_woprof->init_data(W_size,N_problems);
    workload_woprof->init_matmul(matmul_wprof);

    // Finish non kernel related tasks
    clFlush(matmul_woprof->rootQueue[0]);
    clFinish(matmul_woprof->rootQueue[0]);

    cl_time t_start,t_end;
    getTime(&t_start);


    workload_woprof->matmul_ocl(matmul_woprof);

    clFlush(matmul_woprof->rootQueue[0]);
    clFinish(matmul_woprof->rootQueue[0]);

    getTime(&t_end);

	printf("Wo profiling Time \t %d\t %d\t %d \n",t_start,t_end, (t_end-t_start));


    printf("ran programs\n");
    workload_wprof->matmul_profiler->dumpEvents("traces");



}

