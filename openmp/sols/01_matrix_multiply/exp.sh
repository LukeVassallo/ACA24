#!/bin/bash

THREADS=(1 2 4)  # Range of thread values
SIZES=(128 256 512 1024)  # Range of matrix sizes

# Loop over the number of threads
for NUM_THREADS in "${THREADS[@]}"; do
  # Loop over the sizes
  for SIZE in "${SIZES[@]}"; do
    make NUM_THREADS=${NUM_THREADS} SIZE=${SIZE} clean all > /dev/null
    make run 
  done
done
