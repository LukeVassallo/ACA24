#ifndef MATMUL_H
#define MATMUL_H

#include <stdlib.h> // For rand() and RAND_MAX

#ifdef __cplusplus
extern "C" {
#endif

// Function to perform naive matrix multiplication
void naive_matrix_multiply(long long int *A, long long int *B, long long int *C, int m, int n, int p);

// Function to fill a matrix with random values
void fill_matrix_random(long long int *matrix, int rows, int cols);

// Function to fill a matrix with random values
void fill_matrix_zeros(long long int *matrix, int rows, int cols);

#ifdef __cplusplus
}
#endif

#endif // MATMUL_H
