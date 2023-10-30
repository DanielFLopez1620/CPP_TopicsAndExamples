// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * MUTEXES: Were introduced with the pthread library, they only allow one thread at a time to enter
 * a critical section. They are also called 'binary semaphores', because they only accept two states.
 * 
 * They are important to solve data integrity issues when using shared variables.
 * 
 * These are declared with the 'pthread_mutex_t' type, when using them in thread contents you should
 * indicate critical sections with 'pthread_mutex_lock' and 'pthread_mutex_unlock'. Also, in the main,
 * you have to initialize and (in the end) kill the mutex.
 * 
 * Check the code below, which solves the data integrity issue mentioned in the previous module.
 * 
 * If you do not prefer mutex, and want to try with spinlock instaed, you can use them in a similar way,
 * for example, the type is 'pthread_spin_t', the initialization is 'pthread_spin_init, and the destroy,
 * lock and unlock follow the same idea. 
 * 
 * NOTE: When compiling, do not forget the flag -pthread. 
*/

#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* first_thread_content(void* arg);
void* second_thread_content(void* arg);

int main(int argc, char const *argv[])
{
    printf("This code uses threads and there is no data integrity issue...\n");
    
    int shared_integer = 1;

    // Declare threads
    pthread_t th_1;
    pthread_t th_2;

    // Initialize mutex and its resources
    pthread_mutex_init(&mutex, NULL);

    // Creation of threads and passing content
    int res1 = pthread_create(&th_1, NULL, first_thread_content, &shared_integer);
    int res2 = pthread_create(&th_2, NULL, second_thread_content, &shared_integer);

    if( res1 || res2 )
    {
        printf("ERROR... Thread creation wasn't completed\n");
    }

    res1 = pthread_join(th_1, NULL);
    res2 = pthread_join(th_2, NULL);

    if( res1 || res2 )
    {
        printf("ERROR... While joining the threads\n");
    }

    // Similar to pointers, you have to do something in the end with mutexes.
    pthread_mutex_destroy(&mutex);

    return 0;
}


void* first_thread_content(void* arg)
{
    int* shared_resource = (int*)arg;

    // Begin critical section
    pthread_mutex_lock(&mutex);

    // Thread content and usage of shared resource
    (*shared_resource)++;
    printf("Updated with first operation: %d\n", *shared_resource);

    // End critcal section
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* second_thread_content(void* arg)
{
    int* shared_resource = (int*)arg;

    // Begin critical section
    pthread_mutex_lock(&mutex);

    // Thread content and usage of shared resource
    (*shared_resource)*=2;
    printf("Updated with second operation: %d\n", *shared_resource);

    // End critcal section
    pthread_mutex_unlock(&mutex);

    return NULL;
}