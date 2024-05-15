#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define SIZE 134217728
#ifndef NUM_THREADS
	#define NUM_THREADS 2
#endif

// Define the mutex variable
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

// Global variable for accumulating partial sums
double result = 0.0;

// Thread argument structure
struct ThreadArgs {
    double *a;
    double *b;
    int len;
};

// Function to generate a random array of numbers
double* gen_array(int size) {
    double* arr = (double*)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++) {
        arr[i] = 2048 * (((double) rand()) / RAND_MAX - 0.5);
    }
    return arr;
}

// Thread function to calculate the partial sum
void *thread_mac(void *arg) {
    // Extract arguments from the void pointer
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    
    // Calculate the partial sum
    double sum = 0.0;
    for (int i = 0; i < args->len; i++) {
        if (args->a[i] > args->b[i]) {
            sum += (args->a[i] * args->b[i]);
        }
    }

    // TODO: Add code to block access to shared resource and prevent race condition 

    // Critical section of code here
    result += sum;

    // TODO: Add code to release access to shared resource

    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    // Seed random number generator for repeatable results
    srand(42);	

    // Generate two random arrays of numbers
    double* a = gen_array(SIZE);
    double* b = gen_array(SIZE);

    struct timespec start, end;
    double elapsed_time;

    // Define thread IDs and thread argument structures
    pthread_t threads[NUM_THREADS];
    struct ThreadArgs thread_args[NUM_THREADS];

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create threads and calculate partial sums
    for (int i = 0; i < NUM_THREADS; i++) {
        // Set up thread arguments
        thread_args[i].len = (SIZE / NUM_THREADS);
        int offset = thread_args[i].len * i;
        thread_args[i].a = &a[offset];
        thread_args[i].b = &b[offset];

        // Create thread
        // TODO: Initialise NUM_THREADS threads
    }

	// TODO: Suspend program execution untill all threads have completed their task

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Print elapsed time
    printf("NUM_THREADS=%02d, result= %0.6f, Real time: %.9f seconds\n", NUM_THREADS, result, elapsed_time);

    // Free the memory allocated for the arrays
    free(a);
    free(b);

    return 0;
}