// Copyright 2011 www.mpitutorial.com
// Run the command by
// mpicxx -std=c++11 mpi-scatter-gather.c -o mpi-scatter-gather
// mpirun -np 4 ./mpi-scatter-gather 10

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

float compute_average(float *array, int num_of_elements) {
  float sum = 0.f;

  for (int i = 0; i < num_of_elements; i++) {
    sum += array[i];
  }

  return sum / num_of_elements;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: average num_elements_per_proc\n");
    exit(1);
  }

  int num_elements_per_proc = atoi(argv[1]);
  srand(time(NULL));

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  float *rand_nums = NULL;
  if (world_rank == 0) {
    rand_nums = create_rand_nums(num_elements_per_proc * world_size);
  }

  float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);
  assert(sub_rand_nums != NULL);

  MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums,
              num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  float sub_average = compute_average(sub_rand_nums, num_elements_per_proc);

  float *sub_averages = NULL;
  if (world_rank == 0) {
    sub_averages = (float *)malloc(sizeof(float) * world_size);
    assert(sub_averages != NULL);
  }
  MPI_Gather(&sub_average, 1, MPI_FLOAT, sub_averages, 1, MPI_FLOAT, 0,
             MPI_COMM_WORLD);

  if (world_rank == 0) {
    float average = compute_average(sub_averages, world_size);
    printf("Average of all elements is %f\n", average);

    float original_data_average =
        compute_average(rand_nums, num_elements_per_proc * world_size);
    printf("Average computed across original data is %f\n",
           original_data_average);
  }

  if (world_rank == 0) {
    free(rand_nums);
    free(sub_averages);
  }
  free(sub_rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}