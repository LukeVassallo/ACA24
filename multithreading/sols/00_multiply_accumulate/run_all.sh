#!/bin/bash

for (( i=1; i<=256; i*=2 )); do 
    make all NUM_THREADS=$i > /dev/null
    make run
done