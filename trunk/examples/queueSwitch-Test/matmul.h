//! Parameters from Nvidia's example

#include <CL/cl.h>
#include "fission_topology.h"
#include "analysis-devices-utils.h"
#include "eventlist.h"


#ifndef _MATRIXMUL_H_
#define _MATRIXMUL_H_

// Thread block size
#define BLOCK_SIZE 8

// Basic Matrix dimensions (can be amplified by command line switch)
// (chosen as multiples of the thread block size for simplicity)
#define WA (5 * BLOCK_SIZE) // Matrix A width
#define HA (10 * BLOCK_SIZE) // Matrix A height
#define WB (5 * BLOCK_SIZE) // Matrix B width
#define HB WA  // Matrix B height
#define WC WB  // Matrix C width
#define HC HA  // Matrix C height


#define cl_errChk ad_errChk

class matmul
{

   public:
	bool profiling_flag;
    //! N is the number of matmuls we will do
    unsigned int N;
    //! W is the size of each matmul
    unsigned int W;

    float * A;
    float * B;
    float * C;

    //! Reference for baseline
    float * ref;

    ~matmul();

    cl_mem * d_A;
    cl_mem * d_B;
    cl_mem * d_C;

    cl_kernel * multiplicationKernel;

    void init_matmul(fission_topology * topo, bool profiling_flag = ENABLED);
    void init_data(int W, int N );

    void matmul_ocl(fission_topology * topo);
    void baseline(int);
    void baseline_compare(int);

    void computekernel(int problemid, fission_topology * topo, cl_command_queue target_queueue);


    //!Adding profiling to code
    EventList * matmul_profiler ;
};


#endif // _MATRIXMUL_H_
