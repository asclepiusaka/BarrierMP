MPICC = mpicc
#modify MPICH as needed
#MPICH = /usr/local/bin
#MPICH = /home/saka/.openmpi
#-I$(MPICH)/include
CFLAGS = -g -Wall
CLIBS = -lm

all: disbarrier mcsbarrier

disbarrier: disbarrier.o
	$(MPICC) -o $@ $(CFLAGS) $^ $(CLIBS)

mcsbarrier: mcsbarrier.o
	$(MPICC) -o $@ $(CFLAGS) $^

clean:
	rm -f *.o main
