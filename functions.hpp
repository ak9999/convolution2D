// Abdullah Khan

#ifndef __convolution_functions
#define __convolution_functions

#pragma GCC diagnostic ignored "-Wsign-compare"

#include <vector>
#include <iostream>

// OpenCL includes
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

// Convolution function dealing with dynamically allocated 2D arrays.
void convolute(int ** output, int ** input, int ** kernel);

// OpenCL functions
cl_context CreateContext();
cl_command_queue CreateCommandQueue(cl_context, cl_device_id *);
cl_program CreateProgram(cl_context, cl_device_id, const char *);
bool CreateMemObjects(cl_context, cl_mem CreateMemObjects[3], int *, int *);
void Cleanup(cl_context context, cl_command_queue commandQueue, cl_program program, cl_kernel kernel, cl_mem memObjects[3]);

#include "functions.cpp"

#endif // __convolution_functions defined
