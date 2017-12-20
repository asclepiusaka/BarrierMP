# BarrierMP
## Description
This is project 2 of CS 6210, Advanced Operating System, several barriers are implemented using OpenMP and MPI, and synchronize between multiple threads and machines.
different barrier implementations follow the paper [Algorithms for Scalable Synchronization on Shared Memory Multiprocessors](https://www.cs.rice.edu/~johnmc/papers/tocs91.pdf)

two barriers implemented with OpenMP are:
* Count Barrier
* MCS Barrier

two barriers implemented with MPI are:
* MCS Barrier
* Dissemination Barrier

Finally OpenMP MCS Barrier and MPI Dissemination Barrier are combined in an MPI-OpenMP combined program in order to synchronize between multiple cluster nodes that are each running multiple threads.

these programs are tested on Georgia Tech's Jinx cluster.
