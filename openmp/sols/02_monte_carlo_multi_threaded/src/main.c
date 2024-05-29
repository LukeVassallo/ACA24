#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define SAMPLES (int) 1e8 // number of random points to generate

#ifndef NUM_THREADS
    #define NUM_THREADS 2
#endif

char Pi[16] = "3.1415926535897";
char myPi[16] = {0}; 

// Method to compute the precision of pi
int str_identical_index(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] == str2[i]) {
        i++;
    }
    return i-2;
}

int64_t monte_carlo() {
    int64_t points_per_thread = SAMPLES / NUM_THREADS;
    int64_t local_points = 0;
    unsigned int seed = 42 * omp_get_thread_num();
    for (int64_t i = 0; i < points_per_thread; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1.0)
            local_points++;
    }

    return local_points;
}

int main() {
    int hits = 0;
    double pi;

    srand(42);

    omp_set_num_threads(NUM_THREADS);

    struct timespec start, end;
    double elapsed_time;

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    int local_points;
    #pragma omp parallel for 
    for (int i=0; i<NUM_THREADS; i++) {
        local_points = monte_carlo();
        #pragma omp critical
        hits += local_points;
    }

    // Also works ...
    // #pragma omp parallel for reduction(+:hits)
    // for (int i=0; i<NUM_THREADS; i++) {
    //     local_points = monte_carlo();
    //     hits += local_points;
    // }

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Calculate Pi using the ratio of points inside/outside
    pi = 4.0 * ((double)hits / SAMPLES);
    sprintf(myPi, "%.8f", pi);
    printf("Estimated value of Pi using %d threads is %.8f and is accurate up to %d decimal places. Real time: %.9fs.\n", NUM_THREADS, pi, str_identical_index(Pi, myPi), elapsed_time);
    return 0;
}