//
// Created by saka on 10/10/17.
//
#include "../OpenMP/gtmp.h"
#include "../MPI/disbarrier.c"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>
#include <time.h>

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

    struct timespec start,end,duration;

    MPI_Init(&argc, &argv);

    /* Start of Parallel...*/

    /* Making sure that we got the correct number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    mpi_dis_init();
    clock_gettime(CLOCK_MONOTONIC,&start);
#pragma omp parallel
    {

        /*Some code before barrier ..... */
        int thread_num = omp_get_thread_num();
        num_threads = omp_get_num_threads();

        printf("thread %4d of %4d threads from node %4d reaches barrier\n",thread_num,num_threads,rank);

        /* The barrier*/
        int i;
        for(i=0;i<10000;i++) {

            gtmp_barrier();
            if (thread_num == 0) {
                mpi_dis_barrier();
            }
            gtmp_barrier();//OpenMP barrier again
        }

        /*Some code after the barrier..... */
        printf("thread %4d of %4d threads from node %4d get through the barrier\n",thread_num,num_threads,rank);

    }

    clock_gettime(CLOCK_MONOTONIC,&end);
    MPI_Finalize();
    mpi_dis_finalize();
    gtmp_finalize();
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
    printf("average time used in nano second %ld\n",(duration.tv_sec*1000000+duration.tv_nsec/1000));

    return 0;


}
    //seems that node of MPI is not input directly here.


