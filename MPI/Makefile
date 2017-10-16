MPICC = mpicc
#modify MPICH as needed
MPICH = /home/saka/.openmpi
CFLAGS = -I$(MPICH)/include -g -Wall
CLIBS = -lm

all: disbarrier mcsbarrier

disbarrier: disbarrier.o
	$(MPICC) -o $@ $(CFLAGS) $^ $(CLIBS)

mcsbarrier: mcsbarrier.o
	$(MPICC) -o $@ $(CFLAGS) $^

clean:
	rm -f *.o main
