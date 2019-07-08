#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, commsize;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Hello, World!!!\n");
    }
    printf("Rank: %d, size: %d.\n", rank, commsize);

    MPI_Finalize();
    return 0;
}
