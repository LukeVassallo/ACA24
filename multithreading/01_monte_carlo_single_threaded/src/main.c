#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define SAMPLES 1e8 // number of random points to generate

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

int main() {
    int i, hits = 0;
    double x, y, pi;

    srand(42);

    struct timespec start, end;
    double elapsed_time;

    // Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Generate random points and count those that fall within the unit circle
    for (i = 0; i < SAMPLES; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) { // point inside the circle?
            hits++;
        }
    }

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Calculate Pi using the ratio of points inside/outside
    pi = 4.0 * ((double)hits / SAMPLES);
    sprintf(myPi, "%.8f", pi);
    printf("Estimated value of Pi is %.8f and is accurate up to %d decimal places. Real time: %.9fs.\n", pi, str_identical_index(Pi, myPi), elapsed_time);
    return 0;
}