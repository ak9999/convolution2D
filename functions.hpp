#ifndef __convolution_functions
#define __convolution_functions

#pragma GCC diagnostic ignored "-Wsign-compare"

#include <vector>

// Original convolution function dealing with 2D arrays.
//void convolution2D(int (&output)[out_rows][out_cols], int (&input)[in_rows][in_cols], int (&kernel)[k_rows][k_cols]);

// New convolution function dealing with 2D vectors.
void convolutionVec(std::vector<std::vector<int> > &output, std::vector<std::vector<int> > &input, std::vector<std::vector<int> > &kernel);

// OpenCL functions
cl_context CreateContext();
cl_command_queue CreateCommandQueue(cl_context, cl_device_id *);
cl_program CreateProgram(cl_context, cl_device_id, const char *);

bool CreateMemObjects(cl_context, cl_mem memObjects[3], float *, float *);
void Cleanup(cl_context context, cl_command_queue commandQueue,
	           cl_program program, cl_kernel kernel,
						 cl_mem memObjects[3]);

#include "functions.cpp"

#endif // __convolution_functions defined
