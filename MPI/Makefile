MPICC = mpicc
#modify MPICH as needed
MPICH = /usr/lib64/openmpi/1.4-gcc
CFLAGS = -I$(MPICH)/include -g -Wall
CLIBS = -lm

all: disbarrier mcsbarrier

disbarrier: disbarrier.o
	$(MPICC) -o $@ $(CFLAGS) $^ $(CLIBS)

mcsbarrier: mcsbarrier.o
	$(MPICC) -o $@ $(CFLAGS) $^

clean:
	rm -f *.o main
