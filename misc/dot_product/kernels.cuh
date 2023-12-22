#ifndef __KERNELS_CUH__
#define __KERNELS_CUH__

__global__ void dot_product_kernel(float *x, float *y, float *dot, unsigned int n);

#endif
