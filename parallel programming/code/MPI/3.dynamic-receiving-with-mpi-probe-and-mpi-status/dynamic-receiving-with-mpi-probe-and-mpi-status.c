// Copyright 2011 www.mpitutorial.com
// Run the command by 
// mpicc dynamic-receiving-with-mpi-probe-and-mpi-status.c -o dynamic-receiving-with-mpi-probe-and-mpi-status
// mpirun -np 2 dynamic-receiving-with-mpi-probe-and-mpi-status

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if (world_size != 2) {
        fprintf(stderr, "Must use two processes for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int MAX_NUMBERS = 100;
    int numbers[MAX_NUMBERS];
    int number_amount;
    if(world_rank == 0) {
        srand(time(NULL));
        number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;

        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("0 sent %d numbers to 1\n", number_amount);
    } else if(world_rank == 1) {
        // Normal One
        // MPI_Status status;
        // MPI_Recv(numbers, MAX_NUMBERS, MPI_INT, 0,0, MPI_COMM_WORLD, &status);
        // MPI_Get_count(&status, MPI_INT, &number_amount);
        // printf("1 received %d numbers from 0. Message source = %d, tag = %d\n", number_amount, status.MPI_SOURCE, status.MPI_TAG);
        
        // Probe the size first
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &number_amount);
        int* number_buf = (int*)malloc(sizeof(int) * number_amount);

        MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("1 dynamically received %d numbers from 0.\n", number_amount);
        free(number_buf);
    }
    MPI_Finalize();
}