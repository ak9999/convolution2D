// System includes
#include <iostream>
#include <cstdlib>

// Include convolution function
#include "functions.hpp"

// OpenCL includes
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

using namespace std;
