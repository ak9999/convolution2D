// Abdullah Khan
#include "functions.hpp"

// System includes
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

// Ignore warnings about deprecated declarations.
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// Regular convolution function.
void convolute(int ** output, int ** input, int ** kernel)
{
    int convolute = 0; // This holds the convolution results for an index.
    int x, y; // Used for input matrix index

	// Fill output matrix: rows and columns are i and j respectively
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			x = i;
			y = j;

			// Kernel rows and columns are k and l respectively
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					// Convolute here.
					convolute += kernel[k][l] * input[x][y];
					y++; // Move right.
				}
				x++; // Move down.
				y = j; // Restart column position
			}
			output[i][j] = convolute; // Add result to output matrix.
			convolute = 0; // Needed before we move on to the next index.
		}
	}
}

// OpenCL functions
cl_context CreateContext()
{
	cl_int errNum;
 	cl_uint numPlatforms;
 	cl_platform_id firstPlatformID;
 	cl_context context = NULL;

    // Select an OpenCL platform
 	errNum = clGetPlatformIDs(1, &firstPlatformID, &numPlatforms);
	if (errNum != CL_SUCCESS || numPlatforms <= 0)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
 		return NULL;
 	}

	// Create an OpenCL context on the platform.
 	// Default to GPU context first, CPU context next
	cl_context_properties contextProperties[] =
	{
 		CL_CONTEXT_PLATFORM,
 		(cl_context_properties) firstPlatformID,
 		0
 	};

	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU, NULL, NULL, &errNum);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to create an OpenCL GPU context, trying CPU." << std::endl;
		context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU, NULL, NULL, &errNum);
		if (errNum != CL_SUCCESS)
 		{
			std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
 			return NULL;
 		}
	}
 	return context;
}

cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device)
{
	cl_int errNum;
	cl_device_id *devices;
	cl_command_queue commandQueue = NULL;
	size_t deviceBufferSize = -1;

	// Get the size of the devices buffer
	errNum=clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &deviceBufferSize);
	if (errNum!=CL_SUCCESS)
	{
		std::cerr << "Failed call to clGetContextInfo()";
		return NULL;
	}
	if (deviceBufferSize <= 0)
	{
		std::cerr << "No devices available." << std::endl;
		return NULL;
	}

	// Allocate memory for the devices buffer
 	devices = new cl_device_id[deviceBufferSize/sizeof(cl_device_id)];
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, devices, NULL);
 	if (errNum != CL_SUCCESS)
 	{
 		std::cerr << "Failed to get device IDs.";
 		delete[] devices;
 		return NULL;
 	}

	// Choose the first available device
	commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
	if (commandQueue == NULL)
 	{
 		std::cerr << "Failed to create commandQueue for device 0";
		return NULL;
	}
	*device = devices[0];
	delete[] devices;
	return commandQueue;
}

cl_program CreateProgram(cl_context context, cl_device_id device, const char *fileName)
{
	cl_int errNum;
	cl_program program;

	std::ifstream kernelFile (fileName);
	if (!kernelFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << fileName << std::endl;
		return NULL;
	}

	std::ostringstream oss;
	oss << kernelFile.rdbuf();
	std::string srcStdStr = oss.str();
	const char *srcStr = srcStdStr.c_str();
	program = clCreateProgramWithSource(context, 1, (const char **)&srcStr, NULL, NULL);
	if (program == NULL)
 	{
 		std::cerr << "Failed to create CL program from source." << std::endl;
 		return NULL;
	}

	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (errNum != CL_SUCCESS)
 	{
 		// Determine the reason for the error
 		char buildLog[16384];
 		clGetProgramBuildInfo(program, device,
		CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
 		std::cerr << "Error in kernel: " << std::endl;
 		std::cerr << buildLog;
 		clReleaseProgram(program);
 		return NULL;
 	}
 	return program;
}

bool CreateMemObjects(cl_context context, cl_mem memObjects[3], int *a, int *b)
{
 	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*9, a, NULL);
 	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*64, b, NULL);
 	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int)*36, NULL, NULL);
 	if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL)
 	{
 		std::cerr << "Error creating memory objects." << std::endl;
		return 0;
	}
 	return 1;
}

void Cleanup(cl_context context, cl_command_queue commandQueue, cl_program program, cl_kernel kernel, cl_mem memObjects[3])
{
    for (int i=0; i<3; i++)
    {
        if (memObjects[i]!=0)
            clReleaseMemObject(memObjects[i]);
 	}
    if (commandQueue!=0)
        clReleaseCommandQueue(commandQueue);

 	if (kernel!=0)
        clReleaseKernel(kernel);

 	if (program!=0)
        clReleaseProgram(program);

 	if (context!=0)
        clReleaseContext(context);
}
