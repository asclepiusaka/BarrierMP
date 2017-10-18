#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int P;
int logP;
int rank;

void mpi_dis_init(){
	logP = (int)ceil(log2(P));
}

void mpi_dis_barrier(){
	for (int i = 0; i < logP; i++) {
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

int main(int argc, char** argv) {
  int req_processes = 6;
  MPI_Init(&argc, &argv);

  /* Start of Parallel...*/

  /* Making sure that we got the correct number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(P != req_processes){
    fprintf(stderr, "Wrong number of processes.  Required: %d, Actual: %d\n",
    req_processes, P);
    exit(1);
  }
  double t1, t2;
  t1 = MPI_Wtime();

  for (int i = 0; i < 1000; i++) {
    mpi_dis_barrier();
  }

  t2 = MPI_Wtime();

  printf("Average time used in micro second %f\n", (t2 - t1) * 1000000);
   /*
FILE *file = fopen("output", "a");
   mpi_dis_init();
for (int i = 0; i < P; ++i) {
   	if ( rank == i ) {
       	// my turn to write to the file
       	fputs("Process ", file);
       	char snum[5];
       	snprintf(snum, 5, "%d", i);
       	fputs(snum, file);
       	fputs("\n",file);
       	fflush(file);
   	}
   	mpi_dis_barrier();
}
  fclose(file);
  */
   /* Cleanup */ 
   MPI_Finalize();
   mpi_dis_finalize();
   return(0);
}