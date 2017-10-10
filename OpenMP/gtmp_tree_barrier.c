//
// Created by saka on 10/4/17.
//
#include <stdlib.h>
#include "gtmp.h"
#include <omp.h>

/*
    From the MCS Paper: A scalable, distributed tree-based barrier with only local spinning.
    type treenode = record
        parentsense : Boolean
	parentpointer : ^Boolean
	childpointers : array [0..1] of ^Boolean
	havechild : array [0..3] of Boolean
	childnotready : array [0..3] of Boolean
	dummy : Boolean //pseudo-data
    shared nodes : array [0..P-1] of treenode
        // nodes[vpid] is allocated in shared memory
        // locally accessible to processor vpid
    processor private vpid : integer // a unique virtual processor index
    processor private sense : Boolean
    // on processor i, sense is initially true
    // in nodes[i]:
    //    havechild[j] = true if 4 * i + j + 1 < P; otherwise false
    //    parentpointer = &nodes[floor((i-1)/4].childnotready[(i-1) mod 4],
    //        or dummy if i = 0
    //    childpointers[0] = &nodes[2*i+1].parentsense, or &dummy if 2*i+1 >= P
    //    childpointers[1] = &nodes[2*i+2].parentsense, or &dummy if 2*i+2 >= P
    //    initially childnotready = havechild and parentsense = false

    procedure tree_barrier
        with nodes[vpid] do
	    repeat until childnotready = {false, false, false, false}
	    childnotready := havechild //prepare for next barrier
	    parentpointer^ := false //let parent know I'm ready
	    // if not root, wait until my parent signals wakeup
	    if vpid != 0
	        repeat until parentsense = sense
	    // signal children in wakeup tree
	    childpointers[0]^ := sense
	    childpointers[1]^ := sense
	    sense := not sense
*/


typedef struct _node_t {
    char parentsense;
    char *parentpointer;
    char *childpointers[2];
    char havechild[4];
    char childnotready[4];
    char dummy;
} node_t;

node_t * nodes;

char init_sense = 1;

void gtmp_init(int num_threads){
    nodes = malloc(sizeof(node_t)*num_threads);
    int i,j;

    for(i=0;i<num_threads;i++){
        for(j=0;j<4;j++){
            if(4*i+j+1<num_threads){
                nodes[i].havechild[j]=1;
            }else{
                nodes[i].havechild[j]=0;
            }
        }
        if(i!=0){
            nodes[i].parentpointer = &nodes[(i-1)/4].childnotready[(i-1)%4];
        }else{
            nodes[i].parentpointer = &(nodes[i].dummy);
        }

        if(2*i+1<num_threads){
            nodes[i].childpointers[0] = &nodes[2*i+1].parentsense;
        }else{
            nodes[i].childpointers[0] = &nodes[i].dummy;
        }
        if(2*i+2<num_threads){
            nodes[i].childpointers[1] = &nodes[2*i+2].parentsense;
        }else{
            nodes[i].childpointers[1] = &nodes[i].dummy;
        }

        for(j=0;j<4;j++){
            nodes[i].childnotready[j] = nodes[i].havechild[j];
        }
        nodes[i].parentsense = 0;

    }

}

void gtmp_barrier(){
    char sense = init_sense;
    int vpid = omp_get_thread_num();
    int i;
    //spin locally
    while(nodes[vpid].childnotready[0]||nodes[vpid].childnotready[1]||
            nodes[vpid].childnotready[2]||nodes[vpid].childnotready[3]);
    for(i=0;i<4;i++){
        nodes[vpid].childnotready[i] = nodes[vpid].havechild[i];
    }

    *(nodes[vpid].parentpointer) = 0;
    if(vpid!=0){
        while(nodes[vpid].parentsense != sense);
    }
    *nodes[vpid].childpointers[0] = sense;
    *nodes[vpid].childpointers[1] = sense;

    init_sense = !sense;

}

void gtmp_finalize(){
    free(nodes);
}
