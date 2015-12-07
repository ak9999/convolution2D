#include "functions.hpp"

void convolutionVec(std::vector<std::vector<int> > &output, std::vector<std::vector<int> > &input, std::vector<std::vector<int> > &kernel)
{
    int convolute = 0; // This holds the convolution results for an index.
    int x, y; // Used for input matrix index

	// Fill output matrix: rows and columns are i and j respectively
	for (int i = 0; i < output.size() - 1; i++)
	{
		for (int j = 0; j < output[0].size() - 1; j++)
		{
			x = i;
			y = j;

			// Kernel rows and columns are k and l respectively
			for (int k = 0; k < kernel.size() - 1; k++)
			{
				for (int l = 0; l < kernel[0].size() - 1; l++)
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
