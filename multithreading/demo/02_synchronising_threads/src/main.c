#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef NUM_THREADS
	#define NUM_THREADS 2
#endif

// Global variables
pthread_mutex_t mutex; // Mutex variable
int shared_variable = 0; // Shared variable

void *thread_function(void *arg) {
    int *thread_num = (int *)arg;
    printf("Thread %d is running.\n ", *thread_num);

    for (int i=0; i < 1e6; i++) {
        // lock the mutex before accessing the shared resource
        pthread_mutex_lock(&mutex);

        // critical section 
        shared_variable++; // Increment shared variable
        
        if ( *thread_num == 0) break;
        // Unlock mutex after accessing the shared resource
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];
    
    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        printf("%d\n",i);
    }

    printf("Shared variable contains value %d.\n", shared_variable);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
