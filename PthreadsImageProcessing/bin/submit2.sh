#!/usr/bin/env bash 
#SBATCH --job-name=my_test_4 
#SBATCH --account=scw1563 
#SBATCH --nodes=1 
#SBATCH --mem=600mb 
#SBATCH --time=00:5:00

./flip \
	-V \
	../Airbus_Pleiades_50cm_8bit_grey_Yogyakarta.txt \
	output_V_image.txt \
	$SLURM_CPUS_PER_TASK
