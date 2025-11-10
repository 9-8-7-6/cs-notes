// Copyright 2011 www.mpitutorial.com
// Run the command by
// mpicxx -std=c++11 mpi-reduce-and-allreduce.c -o mpi-reduce-and-allreduce
// mpirun -np 4 ./mpi-reduce-and-allreduce 10

#include <assert.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float *create_rand_nums(int num_of_elements) {
  float *rand_nums = (float *)malloc(sizeof(float) * num_of_elements);
  assert(rand_nums != NULL);
  for (int i = 0; i < num_of_elements; i++) {
    rand_nums[i] = (rand() / (float)RAND_MAX);
  }
  return rand_nums;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: avg nums_of_elements_per_process\n");
    exit(1);
  }

  int nums_of_elements_per_process = atoi(argv[1]);

  MPI_Init(NULL, NULL);

  int world_rank;
  int world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  srand(time(NULL) * world_rank);
  float *rand_nums = NULL;
  rand_nums = create_rand_nums(nums_of_elements_per_process);

  float local_sum = 0;
  for (int i = 0; i < nums_of_elements_per_process; i++) {
    local_sum += rand_nums[i];
  }

  printf("Local sum for process %d - %f, avg = %f\n", world_rank, local_sum,
         local_sum / nums_of_elements_per_process);

  float global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (world_rank == 0) {
    printf("Total sum = %f, avg = %f\n", global_sum,
           global_sum / (world_size * nums_of_elements_per_process));
  }

  free(rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}