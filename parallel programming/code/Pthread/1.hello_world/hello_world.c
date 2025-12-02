// Run the command by
// gcc -pthread -Wall -Wextra hello_world.c -o hello_world
// ./hello_wolrd 4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

void *Hello(void* rank);

void *Hello(void* rank) {
    // Use long in case of 64-bit system
    long my_rank = (long) rank;

    printf("Hello from thread %ld of %d\n", my_rank, thread_count);

    return NULL;
}

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <thread_count>\n", argv[0]);
        exit(1);
    }

    // Get number of threads from command line
    thread_count = strtol(argv[1], NULL, 10);

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);        
    }

    printf("Hello from the main thread\n");

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);
    return 0;
}