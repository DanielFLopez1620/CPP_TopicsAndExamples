// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * POSIX THREADS: To explain this, we will need to know more about the 'pthread library', which is
 * a set of headers and functions for writing multithreaded programs (keep in mind that each system
 * have its own implementation, in the case of Linux system is the Native POSIX Threading Library 
 * (NPTL)). The imports are related with 'pthread.h' and some extensions like 'semaphore.h'.
 * 
 * In the main, you can check first a way to spawning them, do not forget the includes, as we will
 * need pthread_create (which would need also a companion function for the thread logic) and pthread_join,
 * check them on the PART 1 of the code.
 * 
 * 
 * NOTE: We use void* becuase it is a generic pointer.
 * 
 * You can test this code with:
 * 
 *      gcc L02_POSIX_threads.c -o thread.out -lpthread
 *      ./thread.out
 * 
 * The option '-lpthread' is needed for linking the program with the existing implementations of the
 * pthread librrary.
 * 
 * Also, you will discover that by joining and detaching, the code will have the same output as they are
 * managed differently.
 * 
*/

#include <stdlib.h>
#include <pthread.h>

void* my_thread_content (void* arg);

int main(int argc, char **argv)
{
    // PART 1: Basics of creating a thread.
    printf("P1: Let's create a thread...");

    // Thread handle variable, in creation it doesn't have Thread ID.
    pthread_t custom_thread;

    // Add content to a thread and fill it with a proper handle, it works as follow:
    // - The first param is related to the thread you want to create
    // - The second param refers to the attributes (stack size, address or detach), if is NULL it is default.
    // - Third params goes for a function pointer which aims to the thread logic
    // It is supposed to return 0 if succeed, otherwise it has an error number.
    int thread_result = pthread_create(&custom_thread, NULL, my_thread_content, NULL);

    // Verify if the pthread creation was completed succesfully
    if(thread_result)
    {
        printf("ERROR! Thread cannot be created: %d", thread_result);
        exit(1);
    }

    // The thread logic isn't executed when created, so you need to join the new thread.
    // It means that you need a parent thread (the main one) and it will be finished when 
    // the companion functions returns. This is implemented with the joint function.
    thread_result = pthread_join(custom_thread, NULL);

    // Verify if the thread was joined
    if(thread_result)
    {
        printf("ERROR! Thread cannot be joined: %d", thread_result);
        exit(2);
    }

    printf("P2: Detached threads\n");

    pthread_t another_thread;

    int result = pthread_create(&another_thread, NULL, my_thread_content, NULL);

    if(result)
    {
        printf("ERROR... Thread cannot be created: %d\n", result);
        exit(1);
    }

    result = pthread_detach(another_thread);

    if(result)
    {
        printf("ERROR... Thread cannot be detached...");
        exit(2);
    }

    // Indication to wait for other detached threads.
    pthread_exit(NULL);

    return 0;
}

/**
 * Generic content of a thread with a simple message for acting as a companion function.
 * 
 * @param arg Generic argument
*/
void* my_thread_content (void* arg)
{
    printf("\n\tThis is the inside of a thread!\n");
    return NULL;
}