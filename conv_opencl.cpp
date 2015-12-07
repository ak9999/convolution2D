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

int main(int argc, char * argv[])
{

    // Set up OpenCL environment

    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
    cl_mem memObjects[3] = {0, 0, 0};
    cl_int errNum;

    // Create Context on first available platform.
    context = CreateContext();

    if(context == NULL)
    {
        cerr << "Failed to create OpenCL context." << endl;
        return -1;
    }

    // Create a command queue on first available device
	commandQueue = CreateCommandQueue(context, &device);
	if(commandQueue == NULL)
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return -1;
	}

	// Create program from "convolution.cl" kernel source
	program = CreateProgram(context, device, "convolution.cl");
	if(program == NULL)
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return -1;
	}

	// Create OpenCL kernel
	kernel = clCreateKernel(program, "convolution_kernel", NULL);
	if(kernel == NULL)
	{
		cerr << "Failed to create kernel." << endl;
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return -1;
	}

    // Create vectors that will be used as arguments to the kernel.

    vector<vector<int>> kernel {
        { 1, 0, 1 },
        { 1, 1, 0 },
        { 0, 0, 1 }
    };

    vector<vector<int>> matrixIn {
        { 1, 0, 1, 0, 1, 0, 0, 0 },
        { 1, 1, 1, 1, 0, 1, 0, 0 },
        { 0, 1, 0, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 1, 1, 1 },
        { 1, 1, 0, 0, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 1, 1, 1 },
        { 1, 0, 1, 0, 1, 0, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    vector<vector<int>> output {
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0 }
    };
    return 0;
}
