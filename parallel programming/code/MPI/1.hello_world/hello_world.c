// Run the command by
// mpicc hello_world.c -p hello_world
// mpirun -np 4 hello_world

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // MPI_Comm_size return the size of a communicator.

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // MPI_Comm_rank return the rank of a processor in a communicator.

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

    MPI_Finalize();
}
