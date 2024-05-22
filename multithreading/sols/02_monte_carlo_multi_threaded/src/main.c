#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Include for int64_t
#include <time.h>
#include <pthread.h>

#ifndef NUM_THREADS
    #define NUM_THREADS 2
#endif

#define NUM_ITERATIONS (int64_t) 1e9 // number of random points to generate

char Pi[16] = "3.1415926535897";
char myPi[16] = {0}; 

// Global variables to hold total points and points within the circle
int64_t total_points = 0;
int64_t points_in_circle = 0;

// Mutex for synchronizing access to shared variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to generate random points and check if they lie within the circle
void *monte_carlo(void *thread_id) {
    int id = *(int *)thread_id;
    int64_t points_per_thread = NUM_ITERATIONS / NUM_THREADS;
    int64_t local_points = 0;
    unsigned int seed = time(NULL) * id;

    for (int64_t i = 0; i < points_per_thread; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1.0)
            local_points++;
    }

    // Update global variables with local counts
    pthread_mutex_lock(&mutex);
    total_points += points_per_thread;
    points_in_circle += local_points;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

// Method to compute the precision of pi
int str_identical_index(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] == str2[i]) {
        i++;
    }
    return i-2;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    //srand(time(NULL));
    srand(42);

    struct timespec start, end;
    double elapsed_time;

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, monte_carlo, (void *)&thread_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Calculate pi
    double pi = 4.0 * ((double)points_in_circle / total_points);
    sprintf(myPi, "%.8f", pi);

    printf("Estimated value of Pi is %.8f and is accurate up to %d decimal places. NUM_THREADS=%04d, Real time: %.9fs.\n", pi, str_identical_index(Pi, myPi), NUM_THREADS, elapsed_time);

    return 0;
}