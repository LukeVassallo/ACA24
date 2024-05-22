#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <assert.h>

#ifndef MATRIX_SIZE
    #define MATRIX_SIZE 512
#endif

double* gen_array(int size) {
    double* arr = (double*)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        arr[i] = 2048 * (((double) rand()) / RAND_MAX - 0.5);
    }
    return arr;
}

void verify_matMul(double *A, double *B, double *C, int m, int n)
{
    for (int i = 0; i < m; i++) 
    {
        int j, k;
        for (j = 0; j < n; j++)
        {
            double tmp = 0;
            for (k = 0; k < n; k++)
            {
                tmp += A[i * m + k] * B[k * m + j];
            }
            assert(tmp == C[i * m + j]);
        }
    }
}

void matrix_multiply_master(double *A, double *B, double *C, int size, int rank, int N, int worker_rows)
{
    if (rank == 0)
    {
        MPI_Request request = MPI_REQUEST_NULL;

        for (int i = 1; i < size; i++)
        {
            MPI_Isend(&A[worker_rows * N * (i - 1)], worker_rows * N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(B, N * N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &request);
        }

        for (int i = worker_rows * (size - 1); i < N; i++)
        {
            int j, k;
            for (j = 0; j < N; j++)
            {
                C[i * N + j] = 0;
                for (k = 0; k < N; k++)
                {
                    C[i * N + j] += A[i * N + k] * B[k * N + j];
                }
            }
        }

        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&C[worker_rows * N * (i - 1)], worker_rows * N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    else
    {
        MPI_Recv(A, worker_rows * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B, N * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < worker_rows; i++)
        {
            int j, k;
            for (j = 0; j < N; j++)
            {
                C[i * N + j] = 0;
                for (k = 0; k < N; k++)
                {
                    C[i * N + j] += A[i * N + k] * B[k * N + j];
                }
            }
        }

        MPI_Request request = MPI_REQUEST_NULL;
        MPI_Isend(C, worker_rows * N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &request);
    }
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    srand(42);
    
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double *A, *B, *C;
    int worker_rows = MATRIX_SIZE / size;

    if (rank == 0)
    {   
        A = gen_array(MATRIX_SIZE * MATRIX_SIZE);
        B = gen_array(MATRIX_SIZE * MATRIX_SIZE);
        C = (double*)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
    }
    else
    {
        A = (double *)malloc(worker_rows * MATRIX_SIZE * sizeof(double));
        B = (double *)malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(double));
        C = (double *)malloc(worker_rows * MATRIX_SIZE * sizeof(double));
    }

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t start_time = clock();

    matrix_multiply_master(A, B, C, size, rank, MATRIX_SIZE, worker_rows);

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t end_time = clock();

    if (rank == 0)
    {
        //verify_matMul(A, B, C, MATRIX_SIZE, MATRIX_SIZE);

        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        double gflops = (2.0 * MATRIX_SIZE * MATRIX_SIZE * MATRIX_SIZE) / (execution_time * 1e9);
        printf("Problem Size: %d, Processes Number: %d, Execution Time: %f sec, Achieved GFLOP/s: %.2f\n", MATRIX_SIZE, size, execution_time, gflops);
    }

    free(A); free(B); free(C);
    MPI_Finalize();

    return 0;
}