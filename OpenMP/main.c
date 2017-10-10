#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "gtmp.h"

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


    /* Code in the block following the #pragma directive is run in parallel */
#pragma omp parallel
    {

        /*Some code before barrier ..... */
        int thread_num = omp_get_thread_num();
        num_threads = omp_get_num_threads();

        printf("thread %4d of %4d threads reaches barrier\n",thread_num,num_threads);

        /* The barrier*/
    gtmp_barrier();

        /*Some code after the barrier..... */
        printf("thread %4d of %4d threads get through the barrier\n",thread_num,num_threads);

    }
    //go over again.
#pragma omp parallel
    {

        /*Some code before barrier ..... */
        int thread_num = omp_get_thread_num();
        num_threads = omp_get_num_threads();

        printf("thread %4d of %4d threads reaches barrier\n",thread_num,num_threads);

        /* The barrier*/
        gtmp_barrier();

        /*Some code after the barrier..... */
        printf("thread %4d of %4d threads get through the barrier\n",thread_num,num_threads);

    }
    gtmp_finalize();

    return(0);
}