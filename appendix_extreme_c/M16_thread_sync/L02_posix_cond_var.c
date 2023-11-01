// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * CONDITION VARIABLES: They are another tool for preventing race condition issues and for keeping
 * the invariant contraint. Do not forget to check the example below, the key here are the 'pthread_cond...'
 * statments and the logic of the wait/sleep thread until a signal is recieved.
*/

#include <stdlib.h>
#include <pthread.h>

// Struct for shared resources and states
typedef struct 
{
    // Flag for states
    int boolean;

    // Mutex for critical sections
    pthread_mutex_t mtx;

    // Condition variable for synchronization
    pthread_cond_t cnd_var;

} shared_state_t;

//  FUNCTION PROTOTYPES
void shared_state_init(shared_state_t *shared_resource);
void shared_state_destroy(shared_state_t* shared_resource);
void* first_thread_content(void*arg);
void* second_thread_content(void*arg);


// MAIN
int main(int argc, char **argv)
{
    shared_state_t shared_resources;

    shared_state_init(&shared_resources);

    pthread_t th1;
    pthread_t th2;

    int res1 = pthread_create(&th1, NULL, first_thread_content, &shared_resources);
    int res2 = pthread_create(&th2, NULL, second_thread_content, &shared_resources);

    if(res1 || res2)
    {
        printf("ERRROR!... Thread cannot be created...");
        exit(1);
    }

    res1 = pthread_join(th1, NULL);
    res2 = pthread_join(th2, NULL);

    if(res1 || res2)
    {
        printf("ERRROR!... Thread cannot be joined...");
        exit(2);
    }

    shared_state_destroy(&shared_resources);

    return 0;
}

// FUNCTIONS DEFINITIONS

/**
 * Like a constructor of shared state for this example.
 * 
 * @param shared_resource POinter to the struct with the mutex, condition and flag.
*/
void shared_state_init(shared_state_t *shared_resource)
{
    shared_resource->boolean = 0;
    pthread_mutex_init(&shared_resource->mtx, NULL);
    pthread_cond_init(&shared_resource->cnd_var, NULL);
}

/**
 * Like a destructor of shared state for this example.
 * 
 * @param shared_resource POinter to the struct with the mutex, condition and flag.
*/
void shared_state_destroy(shared_state_t* shared_resource)
{
    pthread_mutex_destroy(&shared_resource->mtx);
    pthread_cond_destroy(&shared_resource->cnd_var);
}

/**
 * Content of a thread that prints '1°'.
 * 
 * @param arg Generic pointer, it must point to the shared state/resource
*/
void* first_thread_content(void* arg)
{
    shared_state_t* resource = (shared_state_t*) arg;

    // Begin critical section
    pthread_mutex_lock(&resource->mtx);

    printf("1°\n");
    resource->boolean = 1;

    // Notification of completed, remmeber that it can just notify one single thread
    pthread_cond_signal(&resource->cnd_var);

    // End critical section
    pthread_mutex_unlock(&resource->mtx);
    return NULL;
}

/**
 * Content of a thread that prints '2°'.
 * 
 * @param arg Generic pointer, it must point to the shared state/resource
*/
void* second_thread_content(void*arg)
{
    shared_state_t* resource = (shared_state_t*) arg;

    // Begin critical section
    pthread_mutex_lock(&resource->mtx);

    // Loop needed for complete verification of the signal
    while(!resource->boolean)
    {
        // Wait/Sleep for signal validation of the condition variable
        pthread_cond_wait(&resource->cnd_var, &resource->mtx);
    }
    printf("2°\n");

    // End critcal section
    pthread_mutex_unlock(&resource->mtx);
    return NULL;
}