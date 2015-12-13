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


// typedefs
typedef std::mt19937 G;  // mersenne_twister_engine for random numbers
typedef std::uniform_int_distribution<> D; // Distribution range (inclusive)

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

    for(int i = 0; i < 6; i++) // Fill with random values.
    {
        for(int j = 0; j < 6; j++)
            out[(i * 6) + j] = 0;
    }

    convolute(matrix, 8, k_array, 3, out);

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            cout << out[(i * 6) + j] << " ";
        }
        cout << endl;
    }

    delete[] k_array;
    delete[] matrix;
    delete[] out;

    return 0;
}
