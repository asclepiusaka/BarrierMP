OMPFLAGS = -g -Wall -fopenmp -LEVEL1_DCACHE_LINESIZE=`getconf LEVEL1_DCACHE_LINESIZE`
OMPLIBS = -lgomp -lm
CC = gcc
all: test_count test_mcs

test_count: runtest.c gtmp_count_barrier.c
	$(CC) $(OMPFLAGS) -o $@ $^ $(OMPLIBS)

test_mcs: runtest.c gtmp_tree_barrier.c
	$(CC) $(OMPFLAGS) -o $@ $^ $(OMPLIBS)

hello_openmp: main.c
	$(CC) $(OMPFLAGS) -o $@ $^ $(OMPLIBS)

hello_gtmp_count: main.c gtmp_count_barrier.c
	$(CC) $(OMPFLAGS) -o $@ $^ $(OMPLIBS)

hello_gtmp_mcs: main.c gtmp_tree_barrier.c
	$(CC) $(OMPFLAGS) -o $@ $^ $(OMPLIBS)

clean:
	rm -rf *.o test_count test_mcs hello_openmp hello_mpi_* hello_gtmp_* hello_gtmpi_*
