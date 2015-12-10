// Abdullah Khan
// Convolution Matrix without opencl
// System includes
#include <iostream>
#include <cstdlib>
#include <ctime>

// Convolution includes
#include "functions.hpp"

using namespace std;

int main(int argc, char * argv[])
{

    srand(time(0));

    int ** kernel = new int*[3];

    for(int i = 0; i < 3; ++i)
    {
        kernel[i] = new int[3];
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            kernel[i][j] = rand() % 10;
    }

    int ** matrixIn = new int*[8];
    for(int i = 0; i < 8; ++i)
    {
        matrixIn[i] = new int[8];
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
            matrixIn[i][j] = rand() % 10;
    }

    int ** output = new int*[6];
    for(int i = 0; i < 6; ++i)
    {
        output[i] = new int[6];
    }

    for(int i = 0; i < 6; i++)
        output[i][i] = 0;

    convolutionVec(output, matrixIn, kernel);

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