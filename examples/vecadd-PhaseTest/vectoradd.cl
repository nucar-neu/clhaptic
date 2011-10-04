__kernel
void vecadd(__global int *A,
            __global int *B,
            __global int *C) {

   int tid = get_global_id(0);

   C[tid] = A[tid] + B[tid];
   
   return;
}
