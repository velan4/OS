#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function
void* threadFunc(void* arg) {
    printf("Thread is running.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    // (i) Create a thread
    pthread_create(&thread, NULL, threadFunc, NULL);

    // (ii) Join the thread
    pthread_join(thread, NULL);

    // (iii) Check if the thread is equal to the main thread
    if (pthread_equal(thread, pthread_self())) {
        printf("The thread is equal to the main thread.\n");
    } else {
        printf("The thread is not equal to the main thread.\n");
    }

    // (iv) Exit the main thread
    pthread_exit(NULL);
    return 0; // This line will never be reached
}