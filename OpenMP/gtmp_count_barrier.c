//
// Created by saka on 10/4/17.
//
#include "gtmp.h"
#include <stdlib.h>

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
        global_sense^=1;
    }else{
        //spin
        while(my_sense!=global_sense);
    }
}

void gtmp_finalize(){
    //nothing to be done for count barrier!
}
