// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * SEMAPHORES: They are also know because of 'mutex' (which come from mutual exclusion).
 * But sometimes you will need threads (more than 2) to access to a shared resources, so 
 * we can check another type of semaphores, check the code below.
 * 
 * NOTE: This code will not work in a Apple Systems.
*/

#include <stdlib.h>
#include <pthread.h>

// Needed for using sem_t and related
#include <semaphore.h>

// Global semaphore pointer
sem_t *my_sem;

// FUNCTION PROTOTYPES
void* first_thread_content(void* arg);
void* second_thread_content(void* arg);


// MAIN FUNTION
int main(int argc, char **argv)
{
    int shared_resource = 0;

    pthread_t th1;
    pthread_t th2;

    // Create local semaphore (but give global access)
    sem_t local_semaphore;
    my_sem = &local_semaphore;

    // Initialize semaphore (binary) and with only one thread as maximum number of access.
    sem_init(my_sem, 0, 1);

    int res1 = pthread_create(&th1, NULL, first_thread_content, &shared_resource);
    int res2 = pthread_create(&th2, NULL, second_thread_content, &shared_resource);

    if(res1 || res2)
    {
        printf("ERROR.... Thread could not be created...\n");
        exit(1);
    }

    res1 = pthread_join(th1, NULL);
    res2 = pthread_join(th2, NULL);

    if(res1 || res2)
    {
        printf("ERROR... Thread could not be created...");
        exit(2);
    }
    return 0;
}

// FUNCTION DEFINTIONS

/**
 * Generic content of a thread that increments the shared resources in one.
 * 
 * @param arg Generic pointer to the shared resource
 * 
*/
void* first_thread_content(void* arg)
{
    // Point to shared var
    int* shared_resources = (int*)arg;

    // Wait for the semaphore
    sem_wait(my_sem);

    // Real process of the thread
    (*shared_resources)++;
    printf("First thread operation applied...\n");
    
    // Release the semaphore
    sem_post(my_sem);
    return NULL;
}


/**
 * Generic content of a thread that doubles the shared resource value.
 * 
 * @param arg Generic pointer to the shared resource.
 * 
*/
void* second_thread_content(void* arg)
{
    // Point to shared var
    int* shared_resources = (int*)arg;

    // Wait for the semaphore
    sem_wait(my_sem);

    // Real process of the thread
    (*shared_resources) *= 2;
    printf("Second thread operation applied...\n");
    
    // Release the semaphore
    sem_post(my_sem);
    return NULL;
}