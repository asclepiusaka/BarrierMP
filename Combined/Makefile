#MPICH = /home/saka/.openmpi
OMPFLAGS = -g -Wall -fopenmp -LEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE`
OMPLIBS = -lgomp

MPICC = mpicc
#CFLAGS = -I$(MPICH)/include -g -Wall
CFLAGS =  -g -Wall
CLIBS = -lm

all: combined

combined: combined.c ../OpenMP/gtmp_tree_barrier.c
	$(MPICC) -o $@  $(OMPFLAGS) $(CFLAGS) $^ $(CLIBS)


clean:
	rm -f *.o combined
