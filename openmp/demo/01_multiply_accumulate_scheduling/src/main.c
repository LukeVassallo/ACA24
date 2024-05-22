#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#ifndef NUM_THREADS
    #define NUM_THREADS 2
#endif

#define SIZE (int) 1E8
#define CHUNK_SIZE 8

// Function to generate a random array of numbers
double* gen_array(int size) {
    double* arr = (double*)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        arr[i] = 2048 * (((double) rand()) / RAND_MAX - 0.5);
    }
    return arr;
}

int main(void) {
    srand(42);

    omp_set_num_threads(NUM_THREADS);   // Set the number of threads to use

    double *A = gen_array(SIZE);
    //double *B = gen_array(SIZE);
    double *B = (double*)malloc(SIZE * sizeof(double));
    int cond = 0;

    double rand_val = 1.0;
    for (int i = 0; i < SIZE; ++i) {
        // Generate a random number between 0 and 1
        rand_val = (double)rand() / RAND_MAX;
        //if(i % CHUNK_SIZE == 0) rand_val *= -1;

        if (rand_val < 0.5) { 
            cond++;
            B[i] = -fabs(2.0* A[i]);
        }
        else {
            B[i] = fabs(2.0 * A[i]);
        }
    }
    printf("Branch will be taken %0.2f%% of the time.\n",100 * (double)cond/SIZE);

    double start, finish;
    double sum = 0;        
    start = omp_get_wtime();    // Record start time
    {
        #pragma omp parallel for schedule(static, CHUNK_SIZE) num_threads(NUM_THREADS) reduction(+:sum) 
        for (int i = 0; i < SIZE; i++) {
            if (A[i] > B[i]) {
                //#pragma omp critical
                for(int j=0; j<9; j++) sum += (A[i] * B[i]);
            }
        }
        
    }
    finish = omp_get_wtime();   // Record end time

    // Print run information, including elapsed time
    printf("NUM_THREADS=%02d, sum=%0.4e, Real time: %.9f seconds\n", NUM_THREADS, sum, finish-start);

    return 0;
}