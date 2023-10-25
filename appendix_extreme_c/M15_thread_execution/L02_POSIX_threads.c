// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * POSIX THREADS: To explain this, we will need to know more about the 'pthread library', which is
 * a set of headers and functions for writing multithreaded programs (keep in mind that each system
 * have its own implementation, in the case of Linux system is the Native POSIX Threading Library 
 * (NPTL)). The imports are related with 'pthread.h' and some extensions like 'semaphore.h'.
 * 
 * In the main, you can check first a way to spawning them, do not forget the includes.
*/

#include <stdlib.h>
#include <pthread.h>

void* my_thread (void* arg);

int main(int argc, char **argv)
{
    // PART 1: Basics of creating a thread.
    printf("P1: Let's create a thread...");

    pthread_t custom_thread;

    int thread_result = pthread_create(&custom_thread, NULL, my_thread, NULL);

    if(thread_result)
    {
        printf("ERROR! Thread cannot be created: %d", thread_result);
        exit(1);
    }

    thread_result = pthread_join(custom_thread, NULL);

    if(thread_result)
    {
        printf("ERROR! Thread cannot be joined: %d", thread_result);
        exit(2);
    }

    return 0;
}


void* my_thread (void* arg)
{
    printf("This is the inside of a thread!\n");
    return NULL;
}