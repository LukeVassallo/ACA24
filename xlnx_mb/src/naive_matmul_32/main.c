#include <xil_printf.h>		// Lightweight version of printf
#include <xparameters.h>	// Defines all the components in the memory map
#include <xio.h>			// Required for reading / writing memory mapped registers

#include <stdlib.h>			// Required for malloc, srand/rand ..
#include <stdio.h>

#include "matmul.h"
#include "timer.h"

#define ROWS_A 64
#define COLS_A 64
#define ROWS_B 64
#define COLS_B 64

int main()
{

    srand(42);

    if (COLS_A != ROWS_B) {
    	xil_printf("COLS_A=%d and ROWS_B=%d do not match.\r\n", COLS_A, ROWS_B);
    	return -1;
    }

    int *A = (int *)malloc(ROWS_A * COLS_A * sizeof(int));
    int *B = (int *)malloc(ROWS_B * COLS_B * sizeof(int));
    int *C = (int *)malloc(ROWS_A * COLS_B * sizeof(int));

    if (A == NULL || B == NULL || C == NULL) {
    	xil_printf("Memory allocation failed\n");
        return 1;
    }

    fill_matrix_random(A, ROWS_A, COLS_A);
	fill_matrix_random(B, ROWS_B, COLS_B);
	fill_matrix_zeros(C, ROWS_A, COLS_B);

    // Perform matrix multiplication
	start_timer();
	naive_matrix_multiply(A, B, C, ROWS_A, COLS_A, COLS_B);
	double t = stop_timer();

	char s[128] = {};
	sprintf(s, "Time: %.4fs\r\n", t);
	xil_printf("%s",s);

    while(1) naive_matrix_multiply(A, B, C, ROWS_A, COLS_A, COLS_B);

    // Free allocated memory
    free(A);
    free(B);
    free(C);
    return 0;
}
