#include <cuda_runtime.h>
#include <iostream>
#include <memory>

struct CudaDeleter {
    void operator()(float *ptr) const {
        cudaFree(ptr);
    }
};

// CUDA kernel for vector addition
__global__ void vectorAdd(const float* A, const float* B, float* C, int N) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < N) {
        C[idx] = A[idx] + B[idx];
    }
}

int main() {
    int N = 10;
    size_t size = N * sizeof(float);

    // Allocate host memory
    float h_A[N], h_B[N], h_C[N];
    for (int i = 0; i < N; ++i) {
        h_A[i] = static_cast<float>(i);
        h_B[i] = static_cast<float>(i * 2);
    }

    // Allocate device memory
    float* d_A;
    float* d_B;
    float* d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // Create unique_ptrs with the custom deleter
    std::unique_ptr<float, CudaDeleter> deviceA(d_A);
    std::unique_ptr<float, CudaDeleter> deviceB(d_B);
    std::unique_ptr<float, CudaDeleter> deviceC(d_C);

    // Copy input data to device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Launch the CUDA kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // Copy the result back to host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Print the result
    std::cout << "Result of vector addition:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << h_C[i] << " ";
    }
    std::cout << std::endl;

    // Device memory will be automatically freed when unique_ptrs go out of scope

    return 0;
}
