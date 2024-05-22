#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#ifndef SIZE
	#define SIZE 256
#endif

#ifndef NUM_THREADS
	#define NUM_THREADS 2
#endif

double* gen_array(int size) {
    double* arr = (double*)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        arr[i] = 2048 * (((double) rand()) / RAND_MAX - 0.5);
    }
    return arr;
}

void matMulOmp(double *A, double *B, double *C, int m, int n)
{
    // TODO: Parallelise this loop. 
    for (int i = 0; i < m; i++) 
    {
        int j, k;
        for (j = 0; j < n; j++)
        {
            C[i * m + j] = 0;
            for (k = 0; k < n; k++)
            {
                C[i * m + j] += A[i * m + k] * B[k * m + j];
            }
        }
    }
}

int main(void) {
    srand(42);

    // TODO: Specify the number of openMP threads

    double *A = gen_array(SIZE*SIZE);
    double *B = gen_array(SIZE*SIZE);
    double *C = (double*)malloc(SIZE*SIZE * sizeof(double));

    double start, finish;

    // Record start time
    start = omp_get_wtime();
    matMulOmp(A, B, C, SIZE, SIZE);

    // Record end time
    finish = omp_get_wtime();

    // Calculate elapsed time
    printf("NUM_THREADS=%02d, SIZE=%04d, Real time: %.9f seconds\n", NUM_THREADS, SIZE, finish-start);
    return 0;

}