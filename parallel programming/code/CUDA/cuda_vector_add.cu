// Run the command by
// nvcc -o cuda_vector_add cuda_vector_add.cu
// But if driver too old, maybe "nvcc -arch=sm_75 -o cuda_vector_add cuda_vector_add.cu"
// ./cuda_vector_add 10000 10 1024 g

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cuda.h>

__global__ void Vec_add(const float x[], const float y[], float z[], const int n) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    
    if(idx < n)
        z[idx] = x[idx] + y[idx];
}

void Get_args(const int argc, char* argv[], int* n_p, int* blk_ct_p, int* th_per_blk_p, char* i_g){
    if (argc != 5) {
        printf("Usage: ./cuda_vector_add <n> <blocks> <threads_per_block> <mode>\n");
        printf("Argc must be 5\n");
        exit(1);
    }

    *n_p = strtol(argv[1], NULL, 10);
    *blk_ct_p = strtol(argv[2], NULL, 10);
    *th_per_blk_p = strtol(argv[3], NULL, 10);
    *i_g = argv[4][0];

    if (*n_p > (*blk_ct_p) * (*th_per_blk_p)) {
        printf("Total threads (blocks * threads_per_block) is less than n\n");
        exit(1);
    }
}

double Two_norm_diff(const float z[], const float cz[], const int n) {
    double diff, sum = 0.0;

    for (int i=0;i<n;i++) {
        diff = z[i] - cz[i];
        sum += diff*diff;
    }
    return sqrt(sum);
}

int main(int argc, char* argv[]) {
    int n, th_per_blk, blk_ct;
    char i_g;
    
    float *x, *y, *z, *cz;
    double diff_norm;

    Get_args(argc, argv, &n, &blk_ct, &th_per_blk, &i_g);

    cudaMallocManaged((void**)&x, n*sizeof(float));
    cudaMallocManaged((void**)&y, n*sizeof(float));
    cudaMallocManaged((void**)&z, n*sizeof(float));

    cz = (float*) malloc(n*sizeof(float));

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        x[i] = (float)(rand() % 100);
        y[i] = (float)(rand() % 100);
    }

    Vec_add <<<blk_ct, th_per_blk>>>(x, y, z, n);
    cudaDeviceSynchronize();

    for (int i=0;i<n;i++){
        cz[i] = x[i] + y[i];
    }
    
    diff_norm = Two_norm_diff(z, cz, n);
    printf("Two - norm of difference between host and ");
    printf("device = %e\n", diff_norm);

    cudaFree(x);
    cudaFree(y);
    cudaFree(z);

    free(cz);

    return 0;
}