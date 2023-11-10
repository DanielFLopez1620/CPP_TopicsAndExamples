// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * Threads have a private region in the stack (related with the same process), then the threads
 * of the same process can read and modify the stack region of others but it isn't recommended. 
 * 
 * In single thread programs, there is only the main thread, so the usage of the Stack can be
 * same as the process's Stack, but this change when we add more threads. When creating a new
 * thread, a new block is allocated in the Stack region which have a default size. This value
 * can be consulted with:
 * 
 *      ulimit -s # Only works in a POSIX-compliant system
 * 
 * Check the code below to understand how to set or assign a custom stack region for a thread,
 * 
 * You can compile the code with:
 * 
 *      gcc L06_threads_and_stack.c -o stc.out -lpthread
 *      ./stc.out
 * 
 * If you ask yourself, why to set the stack region? Well, you may need it when you use memory-
 * constrained environments or want to improve performance. Check the code 'L07_memory_problem.c'
 * in this module to see an isse of the thread's Stack.
*/

#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

void* first_thread_conten(void* arg);
void* second_thread_conten(void* arg);

int main(int argc, char const *argv[])
{
    // Get min size and use it to calculate the size of a buffer
    size_t buffer_size = PTHREAD_STACK_MIN + 100;

    // Get an allocation in the stack region
    char *buffer = (char*)malloc(buffer_size * sizeof(char));

    // Initialize buffer size
    pthread_t th1;
    pthread_t th2;

    // Create thread with default stack region
    int res1 = pthread_create(&th1, NULL, first_thread_conten, NULL);

    // Create attribute for thread initialization
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Test to set stack for attribute created
    if (pthread_attr_setstack(&attr,buffer, buffer_size))
    {
        printf("ERROR... Thread with custom stack region failed...\n");
        exit(1);
    }

    // Create thread with custom stack region
    int res2 = pthread_create(&th2, &attr, second_thread_conten, NULL);

    if(res1 || res2)
    {
        printf("ERROR... Threads could not be created...\n");
        exit(2);
    }

    printf("Main Thread \n\t> Heap Adress: %p\n", (void*) buffer);
    printf("\t Stack Adress: %p\n", (void*)&buffer_size);

    // Joint threads
    res1 = pthread_join(th1, NULL);
    res2 = pthread_join(th2, NULL);

    if(res1 || res2)
    {
        printf("ERROR... Threads could not be joined...\n");
        exit(3);
    }
    
    free(buffer);

    return 0;
}

/**
 * Simple content of a thread, that creates char variable with the value 'a', and then
 * prints the value.
 * 
 * @param arg Generic pointer to an argument.
*/
void* first_thread_conten(void* arg)
{
    char letter = 'a';
    printf("Th1 > Stack address: %p\n", (void*)&letter);
    return NULL;
}

/**
 * Simple content of a thread, that creates char variable with the value 'a', and then
 * prints the value.
 * 
 * @param arg Generic pointer to an argument.
*/
void* second_thread_conten(void* arg)
{
    char letter = 'b';
    printf("Th2 > Stack address: %p\n", (void*)&letter);
    return NULL;
}