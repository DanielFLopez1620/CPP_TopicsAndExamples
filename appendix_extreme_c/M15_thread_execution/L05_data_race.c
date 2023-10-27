// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Other problems may appear with a shared state, which may lead to problems with the 'data integrity'.
 * 
 * You will discover that increments and related operations are not atomic, so it gives the possibility for
 * interleavings to happen. So, you can check it with:
 * 
 *      gcc L05_data_race.c -o  dr.out -lpthread
 *      ./dr.out
 * 
 * NOTE: Be patient :D
*/

#include <stdlib.h>
#include <pthread.h>

void* first_thread_content(void* arg);
void* second_thread_content(void* arg);

int main(int argc, char **argv)
{
    printf("This code will have problems related with data integrity...\n");
    
    // Shared variable among threads
    int shared_resource = 1;

    // Define thread handlers
    pthread_t action1;
    pthread_t action2;

    // Create new threads and add  the content
    int res1 = pthread_create(&action1, NULL, first_thread_content, &shared_resource);
    int res2 = pthread_create(&action1, NULL, second_thread_content, &shared_resource);

    if (res1 || res2)
    {
        printf("ERROR... The threads could not be created...");
        exit(1);
    }

    // Wait for threads to finish its activity
    res1 = pthread_join(action1, NULL);
    res2 = pthread_join(action2, NULL);

    if (res1 || res2)
    {
        printf("ERROR... The threads could not be be joined...\n");
    }

    return 0;
}

/**
 * General content of a thread that access a shared resource and increment it.
 * 
 * @param arg Pointer to shared resources, integer is recommended.
*/
void* first_thread_content(void* arg)
{
    // Pointer of a shared resource
    int* shared_resource = (int*) arg;

    // Updated value
    (*shared_resource)++;

    // Logging the change
    printf("First thread updated: %d\n", *shared_resource);
    return NULL;
}

/**
 * General content of a thread that access a shared resource and doubles it.
 * 
 * @param arg Pointer to shared resources, integer is recommended.
*/
void* second_thread_content(void* arg)
{
    // Pointer of a shared resource
    int* shared_resource = (int*) arg;

    // Updated value
    *shared_resource *= 2;

    // Logging the change
    printf("Second thread updated: %d\n", *shared_resource);
    return NULL;
}