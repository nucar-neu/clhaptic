#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <unistd.h>
#include "eventlist.h"

#define ELEMENTS 20*1024

char* readSource(const char *sourceFilename);

int main(int argc, char** argv) {

   int *A, *B, *C;
   int *A2;

   int datasize = ELEMENTS * sizeof(int);

   A = new int [datasize];
   B = new int [datasize];
   C = new int [datasize];
   A2 = new int [datasize];

   for(int i = 0; i < ELEMENTS; i++) {
      A[i] = i;
      B[i] = i;
      A2[i] = 0;
   }

   cl_platform_id* platforms;
   cl_uint numPlatforms;
   cl_device_id** devices;
   cl_uint* numDevices;
   cl_context context;
   cl_program program;
   cl_kernel kernel;
   cl_event event;
   EventList* eventList;

   char* source;

   clGetPlatformIDs(0, NULL, &numPlatforms);

   platforms = new cl_platform_id [numPlatforms];
   devices = new cl_device_id* [numPlatforms];

   clGetPlatformIDs(numPlatforms, platforms, NULL);

   numDevices = new unsigned int [numPlatforms];

   char *platformVendor;
   for(int i = 0; i < (int)numPlatforms; i++) {
      printf("Platform %d:\n", i);

      size_t platInfoSize;
      clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 0, NULL,
                        &platInfoSize);

      platformVendor = new char [platInfoSize];

      clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, platInfoSize, 
                        platformVendor, NULL);

      printf("\tVendor: %s\n", platformVendor);
      delete platformVendor;

      clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices[i]);

      printf("\tNumber of devices: %d\n", numDevices[i]);

      devices[i] = new cl_device_id [numDevices[i]];

      clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevices[i], 
                     devices[i], NULL);

      for(int j = 0; j < (int)numDevices[i]; j++) {
         size_t deviceInfoSize;
         char* deviceInfoString;
         printf("\tDevice %d\n", j);
         clGetDeviceInfo(devices[i][j], CL_DEVICE_NAME, 0, NULL, 
                         &deviceInfoSize);
         deviceInfoString = new char [deviceInfoSize];
         clGetDeviceInfo(devices[i][j], CL_DEVICE_NAME, deviceInfoSize,
                         deviceInfoString, NULL);
         printf("\t\tName: %s\n", deviceInfoString);
         delete deviceInfoString;
         clGetDeviceInfo(devices[i][j], CL_DEVICE_VENDOR, 0, NULL, 
                         &deviceInfoSize);
         deviceInfoString = new char [deviceInfoSize];
         clGetDeviceInfo(devices[i][j], CL_DEVICE_VENDOR, deviceInfoSize,
                         deviceInfoString, NULL);
         printf("\t\tVendor: %s\n", deviceInfoString);
         delete deviceInfoString;
      }
   }

   // put a pause here
   int platform = 0;
   int device = 0;
   printf("Enter Device Number: ");
   scanf("%d %d", &platform, &device);

   //cl_int err;
   //context = clCreateContext(NULL, 1, &devices[target], NULL, NULL, &err);

   cl_context_properties cps[3] = {(size_t)CL_CONTEXT_PLATFORM,
         (cl_context_properties)(platforms[platform]), (size_t)0};
   cl_context_properties *cprops = cps;

   context = clCreateContextFromType(cprops, 
                 (cl_device_type)CL_DEVICE_TYPE_ALL, 
                 NULL, NULL, NULL);

   cl_mem d_A, d_B, d_C;
   d_A = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize, NULL, NULL);
   d_B = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize, NULL, NULL);
   d_C = clCreateBuffer(context, CL_MEM_READ_WRITE, datasize, NULL, NULL);

   cl_command_queue commandQ0;
   commandQ0 = clCreateCommandQueue(context, devices[platform][device], 
         CL_QUEUE_PROFILING_ENABLE, NULL);

   eventList = new EventList(context, commandQ0, devices[platform][device], 
         true);

   clEnqueueWriteBuffer(commandQ0, d_A, CL_TRUE, 0, datasize, A,
                        0, NULL, &event);
   eventList->add(event);
   clEnqueueWriteBuffer(commandQ0, d_B, CL_TRUE, 0, datasize, B,
                        0, NULL, &event);
   eventList->add(event);

   source = readSource("vectoradd.cl");
   program = clCreateProgramWithSource(context, 1, (const char**)&source,
                                       NULL, NULL); 
   clBuildProgram(program, 1, &devices[platform][device], NULL, NULL, NULL);

   kernel = clCreateKernel(program, "vecadd", NULL);

   clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_A);
   clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_B);
   clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_C);

   size_t global_work_offset[3] = {0,0,0};
   size_t global_work_size[3] = {ELEMENTS,0,0};
   size_t local_work_size[3] = {ELEMENTS/64,0,0};

   clEnqueueNDRangeKernel(commandQ0, kernel, 1, global_work_offset,
                          global_work_size, local_work_size, 0, NULL,
                          &event);
   eventList->add(event);

   clEnqueueReadBuffer(commandQ0, d_C, CL_TRUE, 0, datasize, C,
                        0, NULL, &event);
   eventList->add(event);

   for(int k = 0; k < 10; k++) {
     printf("C[%d] = %d\n", k, C[k]); 
   }
   int failed = 0;
   for(int k = 0; k < ELEMENTS; k++) {
      if(C[k] != k*2) {
         failed = 1;
      }
   }
   if(failed) {
      printf("RESULTS ARE INCORRECT\n");
   }
   else {
      printf("RESULTS ARE CORRECT\n");
   }


   eventList->printEvents();
   eventList->dumpEvents("eventDumps");

   delete eventList;
   for(int i = 0; i < (int)numPlatforms; i++) {
      delete devices[i];
   }
   delete devices;
   delete numDevices;
   delete platforms;

   return 0;
}

char* readSource(const char *sourceFilename) {

   FILE *fp;
   int err;
   int size;

   char *source;

   printf("source file is: %s\n", sourceFilename);
   fp = fopen(sourceFilename, "r");
   if(fp == NULL) {
      printf("Could not open kernel file: %s\n", sourceFilename);
      exit(-1);
   }

   err = fseek(fp, 0, SEEK_END);
   if(err != 0) {
      printf("Error seeking to end of file\n");
      exit(-1);
   }

   size = ftell(fp);
   if(size < 0) {
      printf("Error getting file position\n");
      exit(-1);
   }

   err = fseek(fp, 0, SEEK_SET);
   if(err != 0) {
      printf("Error seeking to start of file\n");
      exit(-1);
   }

   source = new char [size+1];
   if(source == NULL) {
      printf("Error allocating %d bytes for the program source\n", size+1);
      exit(-1);
   }

   err = fread(source, 1, size, fp);

   if(err != size) {
      printf("only read %d bytes\n", err);
      exit(0);
   }
   printf("read %d bytes\n", size);

   source[size] = '\0';

   return source;
}
