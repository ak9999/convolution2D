// Abdullah Khan
#include "functions.hpp"

// System includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Ignore warnings about deprecated declarations.
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

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

void convolute(const int * input, size_t M, const int * kernel, size_t K, int * r)
{
    for (size_t n = 0; n < M + K - 1; n++)
        for (size_t k = 0; k < std::max(M, K); k++)
            r[n] += (k < M ? input[k] : 0) * (n - k < K ? kernel[n - k] : 0);
}
