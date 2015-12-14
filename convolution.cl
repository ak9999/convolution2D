// convolution.cl
// Convolution Kernel File

__kernel void convolution_kernel(__global const int *k_array,
                                 __global const int *input,
                                 __global int *output)
{
    // 1D convolution requires that we use offsets.
    int offset = get_global_id(0);
    int sum = 0;
    int row = (offset / 6);
    offset = ((row * 8) + (offset % 6));

    // Iterate KERNEL_SIZE times (9 times).
    sum += (k_array[0] * input[offset]);
    sum += (k_array[1] * input[++offset]);
    sum += (k_array[2] * input[++offset]);
    // After the loop iterates 3 times we must enter the next row.
    // Increment offset by 6 to enter next row.
    offset += 6;

    sum += (k_array[3] * input[offset]);
    sum += (k_array[4] * input[++offset]);
    sum += (k_array[5] * input[++offset]);
    offset += 6;

    sum += (k_array[6] * input[offset]);
    sum += (k_array[7] * input[++offset]);
    sum += (k_array[8] * input[++offset]);

    // Set the output equal to the sum.
    output[get_global_id(0)] = ((int)sum);
}
