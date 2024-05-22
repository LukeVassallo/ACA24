#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#ifndef NUM_THREADS
    #define NUM_THREADS 2
#endif

#define SIZE (int) 1E8
#define CHUNK_SIZE 2048

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
    double *B = gen_array(SIZE);

    double start, finish;
    double sum = 0;        
    start = omp_get_wtime();    // Record start time
    {
        #pragma omp parallel for reduction(+:sum) //num_threads(NUM_THREADS)//  schedule(static, CHUNK_SIZE)
        for (int i = 0; i < SIZE; i++) {
            if (A[i] > B[i]) {
               // #pragma omp critical
                sum += (A[i] * B[i]);
            }
        }
        
    }
    finish = omp_get_wtime();   // Record end time

    // Print run information, including elapsed time
    printf("NUM_THREADS=%02d, sum=%0.4e, Real time: %.9f seconds\n", NUM_THREADS, sum, finish-start);

    return 0;
}