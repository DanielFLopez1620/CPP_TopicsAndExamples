// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * BARRIERS: They are needed because some threads are faster than others, so you will need checkpoints.
 * So they must stop and wait for the others to join, and below you can see an example of this implementation.
 * 
 * NOTE: Barriers do not work in macOS, as it is parially POSIX-compliant.
*/

#include <stdlib.h>
#include <pthread.h>

// Declare global barrier type.
pthread_barrier_t barrier;


// FUNCTION PROTOTYPES
void* first_thread_content(void* arg);
void* second_thread_content(void* arg);

// MAIN
int main(int argc, char **argv)
{
    // Initialize a barrier with default mode (NULL) and wait value of 2.
    pthread_barrier_init(&barrier, NULL,2);

    // Create threads and add content
    pthread_t th1;
    pthread_t th2;
    int res1 = pthread_create(&th1, NULL, first_thread_content, NULL);
    int res2 = pthread_create(&th2, NULL, second_thread_content, NULL);

    // Validate creation
    if(res1 || res2)
    {
        printf("ERROR... Thread cannot be created...\n");
        exit(1);
    }

    // Join threads and validate
    res1 = pthread_join(th1, NULL);
    res2 = pthread_join(th2, NULL);

    if(res1 || res2)
    {
        printf("ERROR... Thread cannot be joined...\n");
        exit(2);
    }

    // Do not forget to destroy the barrier, and also do not forget the pointers
    pthread_barrier_destroy(&barrier);
    return 0;
}

// FUNCTION DEFINITIONS

/**
 * Generic content of a thread, that prints first one.
 * 
 * @param arg Generic pointer to an argument.
*/
void* first_thread_content(void* arg)
{
    printf("1°\n");
    pthread_barrier_wait(&barrier);
    return NULL;
}

/**
 * Generic content of a thread, that prints second one.
 * 
 * @param arg Generic pointer to an argument.
*/
void* second_thread_content(void* arg);
{
    pthread_barrier_wait(&barrier);
    printf("2°\n");
    return NULL;
}