#!/bin/bash

#echo -n "Enter the number of iterations (for convergence, independent of other variables) > "
#
#read iter
#
#echo -n "Enter the number of particles > "
#
#read par


module load gsl
module load open_mpi
module load boost

mpic++ -std=c++11 quasi_main.cpp -o exe_quasi_main -I/usr/local/include -L/usr/local/lib -lgsl -lgslcblas

totsim=100
for k in $(seq 0 ${totsim}); do
bsub -n 150 -W 0:59  mpirun ./exe_quasi_main $k
done 

rsync -av --remove-source-files /cluster/scratch/tburcu/quasi burcu@uwis-cx-dock-11-075.ethz.ch:/Users/burcu/desktop/quasi/

