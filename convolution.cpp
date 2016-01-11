// Abdullah Khan
// Convolution Matrix without opencl
// System includes
#include <iostream>
#include <cstdlib>
#include <random>

// Convolution includes
#include "functions.hpp"

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

    int ** kernel = new int*[3];

    for(int i = 0; i < 3; ++i)
    {
        kernel[i] = new int[3];
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            kernel[i][j] = d(g);
    }

    int ** matrixIn = new int*[8];
    for(int i = 0; i < 8; ++i)
    {
        matrixIn[i] = new int[8];
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
            matrixIn[i][j] = d(g);
    }

    int ** output = new int*[6];
    for(int i = 0; i < 6; ++i)
    {
        output[i] = new int[6];
    }

    for(int i = 0; i < 6; i++)
        output[i][i] = 0;

    convolute(output, matrixIn, kernel);

    // Print out the resulting matrix.
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            cout << output[i][j] << " ";
        }
        cout << endl;
    }

    delete[] kernel;
    delete[] matrixIn;
    delete[] output;

    return 0;
}
