#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int *thread_num = (int *)arg;
    printf("Thread %d is running.\n ", *thread_num);
    int *t = malloc(sizeof(int)); 
    *t = rand()%5;
    printf("Thread %d is sleeping for %d.\n ", *thread_num, *t);
    sleep(*t);
    // Perform thread tasks here
    return (void *)t;
}

int main() {
    pthread_t thread1, thread2;
    int thread_num1 = 1, thread_num2 = 2;

    // Create first thread
    pthread_create(&thread1, NULL, thread_function, &thread_num1);
    // Create second thread
    pthread_create(&thread2, NULL, thread_function, &thread_num2);

    // Wait for threads to finish
    void *retVal;
    pthread_join(thread1, &retVal);
    printf("Thread 1 finished with return value %d.\n", *(int*)retVal);
    pthread_join(thread2, &retVal);
    printf("Thread 2 finished with return value %d.\n", *(int*)retVal);

    return 0;
}
