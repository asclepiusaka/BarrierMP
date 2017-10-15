// A mcs-tree barrier using mpi

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

typedef struct mcs_node {
    int arrival_children_ranks[4];
//    char arrival_havechild[4];
    int arrival_parent_rank;
    int wakeup_children_ranks[2];
    int wakeup_parent_rank;

} mcs_node_myt;

static mcs_node_myt *mynode;

void mpi_mcs_init(MPI_Comm comm, int rank, int num_processes) {
    mynode = (mcs_node_myt *)malloc(sizeof(mcs_node_myt));
    for (int i = 0; i < 4; i++) {
        if (4 * rank + i + 1 < num_processes) {
            // have child
            mynode->arrival_children_ranks[i] = 4 * rank + i + 1;
        } else {
            mynode->arrival_children_ranks[i] = -1;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (2 * rank + i + 1 < num_processes) {
            // have child
            mynode->wakeup_children_ranks[i] = 2 * rank + i + 1;
        } else {
            mynode->wakeup_children_ranks[i] = -1;
        }
    }
    if (rank != 0) {
        mynode->arrival_parent_rank = (rank - 1) / 4;
        mynode->wakeup_parent_rank = (rank - 1) / 2;
    } else {
        mynode->arrival_parent_rank = -1;
        mynode->wakeup_parent_rank = -1;
    }
}

void mpi_mcs_barrier(MPI_Comm comm, int rank, int num_processes) {
    for (int i = 0; i < 4; i++) {
        int child_rank = mynode->arrival_children_ranks[i];
        if (child_rank != -1) {
            MPI_Recv(NULL, 0, MPI_INT, child_rank, 0, comm, NULL);
        }
    }
    if (rank != 0) {
        MPI_Send(NULL, 0, MPI_INT, mynode->arrival_parent_rank, 0, comm);
        MPI_Recv(NULL, 0, MPI_INT, mynode->wakeup_parent_rank, 1, comm, NULL);
    }
    for (int i = 0; i < 2; i++) {
        int child_rank = mynode->wakeup_children_ranks[i];
        if (child_rank != -1) {
            MPI_Send(NULL, 0, MPI_INT, child_rank, 1, comm);
        }
    }
    // The barrier did work, but it's too fast that some printing jobs before the barrier may not have finished yet.
    // So we need to slow down explicitly to clearly see the effect of the barrier
    for (int i = 0; i < 2000; i++);
}

void mpi_mcs_finalize() {
    if (mynode) {
        free(mynode);
    }
}

int main(int argc, char** argv) {
    int req_processes = 6;
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

    mpi_mcs_init(MPI_COMM_WORLD, rank, num_processes);

   	FILE *file = fopen("output", "a");
	for (int i = 0; i < num_processes; ++i) {
    	if (rank == i ) {
        	// my turn to write to the file
        	fputs("Process ", file);
        	char snum[5];
        	snprintf(snum, 5, "%d", i);
        	fputs(snum, file);
        	fputs("\n",file);
        	fflush(file);
    	}
    	mpi_mcs_barrier(MPI_COMM_WORLD, rank, num_processes);
	}

    /* Cleanup */
    MPI_Finalize();
    mpi_mcs_finalize();
    return(0);
}