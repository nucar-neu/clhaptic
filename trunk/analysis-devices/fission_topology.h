#include <CL/cl.h>

#include "../profiler/eventtypes.h"

#ifndef _FISSION_TOPLOGY_H_
#define _FISSION_TOPLOGY_H_


#define ROUND_ROBIN  0x100

typedef unsigned int ext_scheduler_type;

//! Allow us to change this anytime later
typedef unsigned int queue_id;

class fission_topology
{
  private:

	bool * queue_profiling_status;

    //! Round robin scheduling
    int last_assigned_queue;

    ext_scheduler_type fission_scheduler;

  public:
    //!Default constructor to set the last assigned queue
    fission_topology();

    //! Regular OpenCL Object Topology
    cl_uint numRootDevices;
    cl_device_id  * devices;
    cl_device_type * root_device_type;
    cl_context root_context;
    cl_command_queue * rootQueue;
    cl_program * root_program;
    void cl_CompileProgramRootDevices(char * kernelPath,
                                    char * compileoptions, bool verbosebuild);


    //! Simple return - cpu or gpu queue interface
    cl_uint cpu_queue_no;
    cl_uint gpu_queue_no;
    cl_command_queue return_cpu_queue();
    cl_command_queue return_gpu_queue();

    //!Fission Related OpenCL Objects
    cl_device_id root_device;
    cl_uint numSubDevices ;
    cl_device_id * subDevices ;
    cl_context subContext;
    cl_command_queue * subQueue;

    //! Populate with more details  - program - one per subdevice
    cl_program * sub_program;


    //! Interface functions
    cl_command_queue return_subqueue();
    void add_problem_subqueue();

    queue_id schedule_kernel();
    //!TODO Command Queue Migration
};

#endif // _FISSION_TOPLOGY_H_
