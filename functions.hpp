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


// Convolution for dynamically allocated pseudo-2D arrays.
void convolute(const int * input, size_t M, const int * kernel, size_t K, int * r);

// OpenCL functions


#include "functions.cpp"

#endif // __convolution_functions defined
