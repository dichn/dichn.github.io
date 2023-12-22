#include <iostream>
#include <random>
#include <thrust/inner_product.h>
#include <thrust/execution_policy.h>

int main() {
    // official example
    float vec1[3] = {1.0f, 2.0f, 5.0f};
    float vec2[3] = {4.0f, 1.0f, 5.0f};
    float result = thrust::inner_product(thrust::host, vec1, vec1 + 3, vec2, 0.0f);
    std::cout << result << std::endl;

    unsigned int n = 1000*256*256;
    float *h_x, *h_y;
    h_x = (float*)malloc(n*sizeof(float));    // culprit for crashdown
    h_y = (float*)malloc(n*sizeof(float));    // culprit for crashdown
    // fill host array with data
	for(unsigned int i=0;i<n;i++){
		h_x[i] = float(rand()%n) / n;
		h_y[i] = float(rand()%n) / n;
	}
    result = thrust::inner_product(thrust::host, h_x, h_x + n, h_y, 0.0f);
    std::cout << result << std::endl;
    return 0;
}

// nvcc thrust.cu -o dot -I /usr/local/cuda/include/ -lcudart -lcuda -L /usr/local/cuda-11.2/lib64/
