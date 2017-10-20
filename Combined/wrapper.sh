#PBS -q cs6210
#PBS -l nodes=8:sixcore
#PBS -l walltime=00:40:00
#PBS -N cdu44_combined

MPIRUN=/usr/lib64/openmpi/bin/mpirun
n=8
echo "======== Combined barrier ========" >> Combined_barrier.txt
echo "running for $n nodes" >> Combined_barrier.txt
for m in 10 11 12
do
	echo "result for $m thread" >> Combined_barrier.txt
	$MPIRUN --hostfile $PBS_NODEFILE -np $n ./OpenMPBarrier/Combined/combined $m >> Combined_barrier.txt
done
