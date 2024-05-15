#include <stdio.h>      // Required for printf
#include <stdlib.h>     // Required for srand, rand
#include <unistd.h>     // Required for sleep
#include <pthread.h>    // Required for all pthread methods 

void *thread_function(void *) {
    int t = rand()%5;
    printf("A thread has started, sleeping for %d.\n", t);
    sleep(t);
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create first thread
    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished execution\n");

    return 0;
}
