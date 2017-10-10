CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall
OMPFLAGS = -g -Wall -fopenmp -LEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE`
OMPLIBS = -lgomp

MPICC = mpicc
CFLAGS = -I$(MPICH)/include

all: combined

combined: combined.c ../OpenMP/gtmp_tree_barrier.c
	$(MPICC) -o $@  $(OMPFLAGS) $^


clean:
	rm -f *.o combined
