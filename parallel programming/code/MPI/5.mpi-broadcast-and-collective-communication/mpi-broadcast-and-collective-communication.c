// Copyright 2011 www.mpitutorial.com
// Run the command by
// mpicxx -std=c++11 mpi-broadcast-and-collective-communication.c -o
// mpi-broadcast-and-collective-communication mpirun -np 4
// ./mpi-broadcast-and-collective-communication 1000 10

#include <assert.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void my_bcast(void *data, int count, MPI_Datatype datatype, int root,
              MPI_Comm communicator) {
  int world_rank;
  MPI_Comm_rank(communicator, &world_rank);
  int world_size;
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) {
    int i;
    for (int i = 0; i < world_size; i++) {
      if (i != world_rank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
      }
    }
  } else {
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compare_bcast num_elements_per_bcast num_bcast\n");
    exit(1);
  }

  int num_elements_per_bcast = atoi(argv[1]);
  int num_bcast = atoi(argv[2]);

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  double total_my_bcast_time = 0.0;
  double total_mpi_bcast_time = 0.0;
  int i;
  int *data = (int *)malloc(sizeof(int) * num_elements_per_bcast);
  assert(data != NULL);

  for (i = 0; i < num_bcast; i++) {
    // Time my_bcast
    // Synchronize before starting timing
    MPI_Barrier(MPI_COMM_WORLD);
    total_my_bcast_time -= MPI_Wtime();
    my_bcast(data, num_elements_per_bcast, MPI_INT, 0, MPI_COMM_WORLD);
    // Synchronize again before obtaining final time
    MPI_Barrier(MPI_COMM_WORLD);
    total_my_bcast_time += MPI_Wtime();

    // Time MPI_Bcast
    MPI_Barrier(MPI_COMM_WORLD);
    total_mpi_bcast_time -= MPI_Wtime();
    MPI_Bcast(data, num_elements_per_bcast, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    total_mpi_bcast_time += MPI_Wtime();
  }

  if (world_rank == 0) {
    printf("Data size = %d, Trials = %d\n",
           num_elements_per_bcast * (int)sizeof(int), num_bcast);
    printf("Avg my_bcast time = %lf\n", total_my_bcast_time / num_bcast);
    printf("Avg MPI_Bcast time = %lf\n", total_mpi_bcast_time / num_bcast);
  }

  free(data);
  MPI_Finalize();
}