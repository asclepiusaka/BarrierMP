//
// Created by saka on 10/4/17.
// a simple sense-reversing barrier implemented in c, to work with openMP. It's naive and easy to understand but demonstrate my understanding about
// multithreading implementation, a more sophisticated barrier implementation can be found in gtmp_tree_barrier.c in the same directory.
#include "gtmp.h"
#include <stdlib.h>
#include <stdio.h>

static int global_sense = 0;
static unsigned int count;
static unsigned int global_number_threads;

void gtmp_init(int number_threads){
    global_number_threads = number_threads;
    count = number_threads;
}

void gtmp_barrier(){
    int  my_sense = global_sense^1;
    if(__sync_fetch_and_sub(&count,1)==1){
        count = global_number_threads;
        global_sense = my_sense;
        //printf("global_sense is %d\n",global_sense);
    }else{
        //spin
        while(my_sense != global_sense);
    }
}

void gtmp_finalize(){
    //nothing to be done for count barrier!
}
