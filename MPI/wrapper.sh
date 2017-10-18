#PBS -q class
#PBS -l nodes=12:sixcore
#PBS -l walltime=00:05:00
#PBS -N pwu80_mpi_10_17
echo "======== MPI dissemination ========" > MPI_dis.txt
echo "======== MPI mcs tree ========" > MPI_mcs.txt

MPIRUN = /usr/lib64/openmpi/bin/mpirun

for n in 2 4 6 8 10 12
do
	echo "result for $n threads" >> MPI_dis.txt
	$MPIRUN -np $n --hostfile $PBS_NODEFILE ./disbarrier >> MPI_dis.txt
	echo "result for $n threads" >> MPI_mcs.txt
    $MPIRUN -np $n --hostfile $PBS_NODEFILE ./mcsbarrier >> MPI_mcs.txt
done

#MPIRUN = /usr/local/bin/mpirun
#MPIRUN = /opt/openmpi-1.4.3-gcc44/bin/mpirun
#AGGR = OMPI_MCA_mpi_yield_when_idle=0