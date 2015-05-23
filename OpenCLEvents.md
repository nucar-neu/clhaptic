# Introduction #

The [| OpenCL specification](http://www.khronos.org/registry/cl/) provides a 'cl\_event' which can be used to store profiling information

# Event States #

Example of OpenCL events

|**Command State** | **Description** |
|:-----------------|:----------------|
|CL\_QUEUED        | Command is in a queue |
|CL\_SUBMITTED     | Command has been submitted to device |
|CL\_RUNNING       | Command is currently executing on device |
|CL\_COMPLETE      | Command has finished execution |

```

cl_int clEnqueueNDRangeKernel (
    cl_command_queue queue,
    cl_kernel kernel, cl_uint work_dim,
    const size_t *global_work_offset,
    const size_t *global_work_size,
    const size_t *local_work_size,
    cl_uint num_events_in_wait_list,
    const cl_event *event_wait_list,
    cl_event *event)

```