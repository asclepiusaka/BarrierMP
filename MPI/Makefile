CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall

MPICC = mpicc
MPICH = /usr/lib64/openmpi/1.4-gcc
CFLAGS = -I$(MPICH)/include

all: srbarrier mcsbarrier

srbarrier: srbarrier.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

mcsbarrier: mcsbarrier.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f *.o main
