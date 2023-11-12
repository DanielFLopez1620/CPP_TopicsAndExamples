// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * The Heap and Data segment are accessible by all the threads, but as you should remember, the Heap
 * is dynamic, so threads can access to the content while the process is running. Also, keep in mind 
 * that the memory managment here is important, as the meomory should be allocated and dellocated to
 * prevent memory leaks.
 * 
 * When using threads and heap, the key point it to prevent dangling pointers. Here in the code below
 * you can watch an example of WHAT CAN GO WRONG if no mechanism are implemented.
 * 
 * NOTE: When using threads, the deallocation should be also secure to prevent the pointers to become
 * dangling. A proposal is presented below.
*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Create a custom message for a pthread error.
#define CHECK_RESULT(result) \
    if (result) \
    { \
    printf("Unknown error with a thread happened...\n"); \
    exit(1); \
    }

// Pointer to a shared array of letter
char* shared_resource;

// Size of the array make global to use it as a max
unsigned int size_array;

// Booleans created
int TRUE = 1;
int FALSE = 0;

// Crete barrier for the threads functions and contents
pthread_barrier_t alloc_barrier;
pthread_barrier_t fill_barrier;
pthread_barrier_t done_barrier;

// Function Prototypes
void* thread_malloc(void* arg);
void* thread_fill(void* arg);
void* thread_print_body(void* arg);
void thread_dealloc(void* arg);

// MAIN
int main(int argc, char **argv)
{
    printf("Check this code inside to understand using threads safetly with the Heap.\n");

    shared_resource = NULL;

    pthread_barrier_init(&alloc_barrier, NULL, 3);
    pthread_barrier_init(&fill_barrier, NULL, 3);
    pthread_barrier_init(&done_barrier, NULL, 2);

    pthread_t malloc_thread;
    pthread_t fill_thread_1;
    pthread_t fill_thread_2;
    pthread_t print_thread;
    pthread_t dealloc_thread;

    pthread_attr_t attribute;
    pthread_attr_init(&attribute);
    int res = pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_DETACHED);
    CHECK_RESULT(res); // Using macro to log errors

    res = pthread_create(&malloc_thread, &attribute, thread_malloc, NULL);
    CHECK_RESULT(res); // Using macro to log errors

    res = pthread_create(&fill_thread_1, &attribute, thread_fill, &TRUE);
    CHECK_RESULT(res); // Using macro to log errors

    res = pthread_create(&fill_thread_2, &attribute, thread_fill, &FALSE);
    CHECK_RESULT(res); // Using macro to log errors

    res = pthread_create(&print_thread, &attribute, thread_print_body, NULL);
    CHECK_RESULT(res); // Using macro to log errors

    res = pthread_create(&dealloc_thread, &attribute, thread_dealloc, NULL);
    CHECK_RESULT(res);

    // Finish usage of threads and program
    pthread_exit(NULL);
    return 0;
}

// FUNCTION DEFINITIONS

/**
 * Generic function to allocate a shared resource
 * 
 * @param Arg Generic pointer to an argument.
*/
void* thread_malloc(void* arg)
{
    size_array = 20;
    shared_resource = (char*) malloc(size_array * sizeof(char*));
    pthread_barrier_wait(&alloc_barrier);
    return NULL;
}

/**
 * Generic function to fill a thread, with letters
 * 
 * @param Arg Generic pointer to an argument, checks for a boolean to initialize value
*/
void* thread_fill(void* arg)
{
    pthread_barrier_wait(&alloc_barrier);
    int value = *((int*)arg);
    char letter = 'a';
    size_t begin = 1;
    if (value)
    {
        letter = 'z';
        begin = 0;
    }
    for(size_t i = begin; i < size_array; i += 2)
    {
        shared_resource[i] = value ? letter-- : letter++;
    }
    shared_resource [size_array - 1] = '\0';
    pthread_barrier_wait(&fill_barrier);
    return NULL;
}

/**
 * Generic function print a shared resource
 * 
 * @param Arg Generic pointer to an argument.
*/
void* thread_print_body(void* arg)
{
    pthread_barrier_wait(&fill_barrier);
    printf("Content: %s\n", shared_resource);
    pthread_barrier_wait(&done_barrier);
    return NULL;
}

/**
 * Generic function to deallocate a shared resource and kill all the barriers.
 * 
 * @param Arg Generic pointer to an argument.
*/
void thread_dealloc(void* arg)
{
    pthread_barrier_wait(&done_barrier);
    free(shared_resource);
    pthread_barrier_destroy(&alloc_barrier);
    pthread_barrier_destroy(&fill_barrier);
    pthread_barrier_destroy(&done_barrier);
    return NULL;
}
