// Abdullah Khan

// System includes
#include <iostream>
#include <cstdlib>
#include <random>

// Include convolution function
#include "functions.hpp"

// OpenCL includes
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

// using-declarations
using G = std::mt19937; // mersenne_twister_engine for random numbers
using D = std::uniform_int_distribution<>; // Distribution range (inclusive)

// namespaces
using namespace std;

int main(int argc, char * argv[])
{
    // For randomly generating numbers.
    G g;
    g.seed(random_device()());
    D d(0, 9); // Random number in range.
    // Create arrays that will be used as arguments to the kernel.

    int * k_array = new int[3*3]; // Initialize.

    for(int i = 0; i < 3; i++) // Fill it with random values 0-9.
    {
        for(int j = 0; j < 3; j++)
            k_array[(i * 3) + j] = d(g);
    }

    int * matrix = new int[8*8]; // Initialize.

    for(int i = 0; i < 8; i++) // Fill with random values.
    {
        for(int j = 0; j < 8; j++)
            matrix[(i * 8) + j] = d(g);
    }

    int * out = new int[6*6]; // Initialize.

    for(int i = 0; i < 6; i++) // Fill with 0.
    {
        for(int j = 0; j < 6; j++)
            out[(i * 6) + j] = 0;
    }

    // Convolution happens here.

    // Set up OpenCL environment.
    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
    cl_mem memObjects[3] = {0,0,0};
    cl_int errNum;

    //Create an OpenCL context on first available platform
    context = CreateContext();
    if(context == NULL)
    {
        cerr << "Failed to create OpenCL context." << endl;
        return 1;
    }

    //Create a command queue on first available device
    commandQueue = CreateCommandQueue(context, &device);
    if(commandQueue == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    //Create program from "HelloWorld.cl" kernel source
    program = CreateProgram(context, device, "convolution.cl");
    if(program == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    //Create OpenCL kernel
    kernel = clCreateKernel(program, "convolution_kernel", NULL);
    if(kernel == NULL)
    {
        cerr << "Failed to create kernel." << endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return true;
    }

    if(CreateMemObjects(context, memObjects, matrix, k_array) == false)
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

	//Set the kernel arguments
	errNum = clSetKernelArg(kernel, 0 , sizeof(cl_mem), &memObjects[0]);
	errNum = clSetKernelArg(kernel, 1 , sizeof(cl_mem), &memObjects[1]);
	errNum = clSetKernelArg(kernel, 2 , sizeof(cl_mem), &memObjects[2]);
	if(errNum != CL_SUCCESS)
	{
		cerr << "Error setting kernel arguments." << endl;
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}
	size_t globalWorkSize[1] = {36};
	size_t localWorkSize[1] = {1};

	//Queue the kernel up for execution across the array
	errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	if(errNum != CL_SUCCESS)
	{
		cerr << "Error ." << endl;
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

	//Transfer the result from buffer back to host
	errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE, 0, sizeof(int)*36, out, 0, NULL, NULL);
	if(errNum != CL_SUCCESS)
	{
		cerr << "Error reading result buffer." << endl;
		Cleanup(context, commandQueue, program, kernel, memObjects);
		return 1;
	}

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            cout << out[(i * 6) + j] << " ";
        }
        cout << endl;
    }

    Cleanup(context, commandQueue, program, kernel, memObjects);

    delete[] k_array;
    delete[] matrix;
    delete[] out;

    return 0;
}
