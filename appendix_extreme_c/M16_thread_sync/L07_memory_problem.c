// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and can lead to crashes, as there are some interleavings.

#include <stdio.h>

/**
 * If you run this code multiple times, there is a chance that the pointer become dangling, so there is also
 * a chance for crashes, as there is an interleaving here.
 * 
 * This is the case you need to analize in order to determinate what a proper sunchronization
 * should be used. If you haven't notice, the problem of the code below is the shared resource and then
 * the order the threads could be called.
*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int* shared_resource;

void* first_thread_content(void* arg);
void* second_thread_content(void* arg);

int main(int argc, char **argv)
{
    shared_resource = NULL;

    pthread_t th1;
    pthread_t th2;

    pthread_create(&th1, NULL, first_thread_content, NULL);
    pthread_create(&th2, NULL, second_thread_content, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}

/**
 * Generic content of a thread, that saves a number by using its access to a global pointer.
 * 
 * @param arg Generic pointer to an argument.
*/
void* first_thread_content(void* arg)
{
    int local_num = 1620;
    shared_resource = &local_num;
    usleep(10);
    return NULL;
}

/**
 * Generic content of a thread, that saves prints a number by using its access to a global pointer.
 * 
 * @param arg Generic pointer to an argument.
*/
void* second_thread_content(void* arg)
{
    printf("Num: %d\n", *shared_resource);
    return NULL;
}