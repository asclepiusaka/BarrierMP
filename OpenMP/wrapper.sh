#PBS -q cs6210
#PBS -l nodes=1:sixcore
#PBS -l walltime=00:05:00
#PBS -N cdu44_openmp
echo "======== OpenMP_sense_reversing ========" > OpenMP_sense_reversing.txt
echo "======== OpenMP_mcs ========" > OpenMP_mcs.txt
for n in 2 3 4 5 6 7 8
do
	echo "result for $n threads" >> OpenMP_sense_reversing.txt
	./OpenMPBarrier/OpenMP/test_count $n >> OpenMP_sense_reversing.txt
	echo "result for $n threads" >> OpenMP_mcs.txt
    ./OpenMPBarrier/OpenMP/test_mcs $n >> OpenMP_mcs.txt
done