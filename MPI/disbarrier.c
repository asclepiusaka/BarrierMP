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
  struct timespec start, end, duration;
  clock_gettime(CLOCK_MONOTONIC, &start);

  for (int i = 0; i < 1000; i++) {
    mpi_dis_barrier();
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  duration.tv_sec =  end.tv_sec - start.tv_sec;
  duration.tv_nsec = end.tv_nsec - start.tv_nsec;
  while (duration.tv_nsec > 1000000000) {
    duration.tv_sec++;
    duration.tv_nsec -= 1000000000;
  }
  while (duration.tv_nsec < 0) {
    duration.tv_sec--;
    duration.tv_nsec += 1000000000;
  }
  printf("Average time used in nano second %ld\n", (duration.tv_sec*100000+duration.tv_nsec/10000));
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