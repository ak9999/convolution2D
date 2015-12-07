// Convolution Matrix without opencl
// System includes
#include <iostream>

// Convolution includes
#include "functions.hpp"

using namespace std;

int main(int argc, char * argv[])
{
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

    return 0;
}
