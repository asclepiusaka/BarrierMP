//
// Created by saka on 10/10/17.
//
#include "../OpenMP/gtmp.h"
#include "../MPI/srbarrier.c"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr,"please input number of threads");
    }
    int num_processes;
    int rank;
    int num_threads;

    //Open MP
    num_threads = atoi(argv[1]);

    /* Prevents runtime from adjusting the number of threads. */
    omp_set_dynamic(0);

    /* Making sure that it worked. */
    if (omp_get_dynamic())
        printf("Warning: dynamic adjustment of threads has been set\n");

    /* Setting number of threads */
    omp_set_num_threads(num_threads);
    gtmp_init(num_threads);

    //mpi


    MPI_Init(&argc, &argv);

    /* Start of Parallel...*/

    /* Making sure that we got the correct number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

#pragma omp parallel
    {

        /*Some code before barrier ..... */
        int thread_num = omp_get_thread_num();
        num_threads = omp_get_num_threads();

        printf("thread %4d of %4d threads from node %4d reaches barrier\n",thread_num,num_threads,rank);

        /* The barrier*/
        gtmp_barrier();
        if (thread_num==0)
        {
            mpi_sr_barrier(MPI_COMM_WORLD, rank, num_processes);
        }
        gtmp_barrier();//OpenMP barrier again

        /*Some code after the barrier..... */
        printf("thread %4d of %4d threads from node %4d get through the barrier\n",thread_num,num_threads,rank);

    }

    MPI_Finalize();
    gtmp_finalize();

    return 0;


}
    //seems that node of MPI is not input directly here.


