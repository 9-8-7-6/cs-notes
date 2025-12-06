// Run the command by
// nvcc -o cuda_hello cuda_hello.cu
// But if driver too old, maybe "nvcc -arch=sm_75 -o cuda_hello cuda_hello.cu"
// ./cuda_hello 1

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void Hello(void) {
    printf("Hello from thread %d!\n", threadIdx.x);     
}

int main(int argc, char* argv[]) {
    int thread_count;

    if (argc > 1) {
        thread_count = strtol(argv[1], NULL, 10);
    } else {
        thread_count = 1;
    }

    if (thread_count <= 0) {
        fprintf(stderr, "invalid thread_count\n");
        return 1;
    }

    Hello <<<1, thread_count>>>();      

    cudaDeviceSynchronize();

    return 0;
}
