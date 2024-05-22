#!/bin/bash

PROCS=(1 2 4)  # Number of processes to spawn
MATRIX_SIZES=(128 256 512 1024)  # Example sizes

# Loop over the number of threads
for NUM_PROCS in "${PROCS[@]}"; do
  # Loop over the sizes
  for MATRIX_SIZE in "${MATRIX_SIZES[@]}"; do
    #echo "Running with NUM_THREADS=$NUM_THREADS and SIZE=$SIZE"
    make MATRIX_SIZE=${MATRIX_SIZE} clean all > /dev/null
    make PROCS=${NUM_PROCS} run 
  done
done
