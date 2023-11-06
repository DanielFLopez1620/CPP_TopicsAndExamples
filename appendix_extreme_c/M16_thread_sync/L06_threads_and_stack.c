// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

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
 * 
 * 
 * 
*/

#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

void* first_thread_conten(void* arg);
void* second_thread_conten(void* arg);

int main(int argc, char const *argv[])
{
    size_t buffer_size = PTHREAD_STACK_MIN + 100;
    char *buffer = (char*)malloc(buffer_size * sizeof(char));

    pthread_t th1;
    pthread_t th2;

    int res1 = pthread_create(&th1, NULL, first_thread_conten, NULL);
    int res2 = pthread_create(&th2, NULL, second_thread_conten, NULL);

    if(res1 || res2)
    {
        printf("ERROR... Threads could not be joined...\n");
        exit(2);
    }

    printf("Main Thread \n\t> Heap Adress: %p\n", (void*) buffer);
    printf("\t Stack Adress: %p\n", (void*)&buffer_size);
    
    return 0;
}


void* first_thread_conten(void* arg)
{
    char letter = 'a';
    printf("Th1 > Stack address: %p\n", (void*)&letter);
    return NULL;
}
void* second_thread_conten(void* arg)
{
    char letter = 'b';
    printf("Th2 > Stack address: %p\n", (void*)&letter);
    return NULL;
}