// A sense-reversing barrier using mpi

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

char sense = 1;

void mpi_sr_barrier(MPI_Comm comm, int rank, int num_processes){
    sense = !sense;
    if (rank > 0) {
        MPI_Send(NULL, 0, MPI_INT, 0, sense, comm);
        MPI_Recv(NULL, 0, MPI_INT, 0, sense, comm, NULL);
    } else {
        for (int i = 1; i < num_processes; i++) {
            MPI_Recv(NULL, 0, MPI_INT, i, sense, comm, NULL);
        }
        // All processes reached the barrier.
        for (int i = 1; i < num_processes; i++) {
            MPI_Send(NULL, 0, MPI_INT, i, sense, comm);
        }
    }
    // The barrier did work, but it's too fast that some printing jobs before the barrier may not have finished yet.
    // So we need to slow down explicitly to clearly see the effect of the barrier
//    for (int i = 0; i < 2000; i++);
    return;
}

int main(int argc, char** argv)
{
    int req_processes = 30;
    int num_processes;
    int rank;

    MPI_Init(&argc, &argv);

    /* Start of Parallel...*/

    /* Making sure that we got the correct number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(num_processes != req_processes){
        fprintf(stderr, "Wrong number of processes.  Required: %d, Actual: %d\n",
                req_processes, num_processes);
        exit(1);
    }
    fprintf(stdout, "Barrier Pos 1 : Process %d of %d\n", rank+1, num_processes);
    fflush(stdout);
    /* The barrier */
    mpi_sr_barrier(MPI_COMM_WORLD, rank, num_processes);
    fprintf(stdout, "Barrier Pos 2 : Process %d of %d\n", rank+1, num_processes);
    fflush(stdout);
    mpi_sr_barrier(MPI_COMM_WORLD, rank, num_processes);
    fprintf(stdout, "Barrier Pos 3 : Process %d of %d\n", rank+1, num_processes);
    fflush(stdout);
/* Code after barrier ...*/

    /* Cleanup */
    MPI_Finalize();
    return(0);
}