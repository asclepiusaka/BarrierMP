#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define _POSIX_C_SOURCE >= 199309L
#include <time.h>

int P;
int logP;
int rank;

void mpi_dis_init(){
	logP = (int)ceil(log2(P));
}

void mpi_dis_barrier(){
    int i;
	for (i = 0; i < logP; i++) {
		MPI_Send(NULL, 0, MPI_INT, (rank + (int)pow(2, i)) % P, 0, MPI_COMM_WORLD);
		int source = rank - (int)pow(2,i); // Will only be smaller than P
		if (source < 0) {
			source = P + source;
		}
		MPI_Recv(NULL, 0, MPI_INT, source, 0, MPI_COMM_WORLD, NULL);
	}
}

void mpi_dis_finalize() {
	return;
}
