//
// Created by saka on 10/13/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "gtmp.h"
#include <time.h>


int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr,"please input number of threads");

    }
    int num_threads;
    num_threads = atoi(argv[1]);
    /* Prevents runtime from adjusting the number of threads. */
    omp_set_dynamic(0);

    /* Making sure that it worked. */
    if (omp_get_dynamic())
        printf("Warning: dynamic adjustment of threads has been set\n");

    /* Setting number of threads */
    omp_set_num_threads(num_threads);
    gtmp_init(num_threads);

    struct timespec start,end,duration;



    clock_gettime(CLOCK_MONOTONIC,&start);
    /* Code in the block following the #pragma directive is run in parallel */
#pragma omp parallel
    {
        int i;
        /*Some code before barrier ..... */
        for(i=0;i<100000;i++)
            gtmp_barrier();


        /*Some code after the barrier..... */


    }
    //go over again.
    clock_gettime(CLOCK_MONOTONIC,&end);
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
    printf("average time used in nano second %ld\n",(duration.tv_sec*100000+duration.tv_nsec/10000));

    return(0);
}
