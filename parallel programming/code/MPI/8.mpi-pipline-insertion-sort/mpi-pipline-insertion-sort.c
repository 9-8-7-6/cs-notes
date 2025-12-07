// Run the command by
// mpicxx -std=c++11 mpi-pipline-insertion-sort.c -o mpi-pipline-insertion-sort
// mpirun -np 4 ./mpi-pipline-insertion-sort

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAG_DATA 0
#define TAG_END 1

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_val = -1;
    int has_local = 0;
    int incoming;
    MPI_Status status;

    if (rank == 0) {
        srand(time(NULL));
        int *input_array = (int*)malloc(size * sizeof(int));

        printf("Original: ");
        for (int i = 0; i < size; ++i) {
            input_array[i] = rand() % 100;
            printf("%d ", input_array[i]);
        }
        printf("\n");

        local_val = input_array[0];
        has_local = 1;

        for (int i = 1; i < size; i++) {
            if(input_array[0] > input_array[i]) {
                std::swap(input_array[0] , input_array[i]);
            }

            MPI_Send(&input_array[i], 1, MPI_INT, 1, TAG_DATA, MPI_COMM_WORLD);
        }

        MPI_Send(NULL, 0, MPI_INT, 1, TAG_END, MPI_COMM_WORLD);

        free(input_array);
    }

    if(rank != 0) {
        while (1) {
            MPI_Recv(&incoming, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (status.MPI_TAG == TAG_END) {
                if (rank < size - 1) {
                    MPI_Send(NULL, 0, MPI_INT, rank + 1, TAG_END, MPI_COMM_WORLD);
                }
                break;
            }

            if (!has_local) {
                local_val = incoming;
                has_local = 1;
            } else {
                int to_send;
                if (incoming < local_val) {
                    to_send = local_val;
                    local_val = incoming;
                } else {
                    to_send = incoming;
                }
                
                if (rank < size - 1) {
                    MPI_Send(&to_send, 1, MPI_INT, rank + 1, TAG_DATA, MPI_COMM_WORLD);
                }
            }
        }
    }

    int *sorted_array = NULL;
    if (rank == 0) {
        sorted_array = (int*)malloc(size * sizeof(int));
    }

    MPI_Gather(&local_val, 1, MPI_INT, sorted_array, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sorted:   ");
        for (int i = 0; i < size; i++) {
            printf("%d ", sorted_array[i]);
        }
        printf("\n");
        free(sorted_array);
    }

    MPI_Finalize();
    return 0;
}
