#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

const int size=100; // in megabytes
const int N=100;

int main(int argc, char *argv[]) {
    int rank, commsize, i;
    int sender_rank=0, reciever_rank;
    int matrixsize=size*1024*1024/sizeof(int);

    int *buffer=malloc(matrixsize*sizeof(int));
    MPI_Status status;

    double t_start, t_end;
    double c_start, c_end;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Rank: %d, size: %d.\n",rank,commsize);
    reciever_rank=commsize-1;

    if (commsize < 2) {
        printf("Please run with at least two processes.\n");fflush(stdout);
        MPI_Finalize();
        return 0;
    }

    t_start=MPI_Wtime();

    if (rank == sender_rank) {
        for (i=0; i<N; i++) {
            c_start=MPI_Wtime();
	    MPI_Send(buffer, matrixsize, MPI_INT, reciever_rank, 123, MPI_COMM_WORLD);
	    c_end=MPI_Wtime();
            printf("Send: i=%d iter_duration=%f\n", i, c_end - c_start);
	}
    }
    if (rank == reciever_rank) {
        for (i=0; i<matrixsize; i++)
            buffer[i] = -1;
        for (i=0; i<N; i++) {
            c_start=MPI_Wtime();
            MPI_Recv(buffer, matrixsize, MPI_INT, sender_rank, 123, MPI_COMM_WORLD, &status);
            c_end=MPI_Wtime();
            printf("Recv: i=%d iter_duration=%f\n", i, c_end - c_start);
	}
    }

    t_end=MPI_Wtime();

    if (rank == sender_rank || rank == reciever_rank) {
	printf("Rank %d exited. %d*%d mb in %f sec. %f mb/sec\n",rank,N,size, t_end-t_start, (N*size)/(t_end-t_start) );
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}
