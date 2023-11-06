// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * There would be cases when you do not need binary semaphores, so you will need to implement a
 * more general case, or you need to create more threads. So, let's check the example of water
 * molecules.
 * 
 * NOTE: Again, this code will not work on Apple systems, as you will need to implement your own
 * semaphores.
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h> // Errno and strerror
#include <pthread.h> // POSIX standart header for threads
#include <semaphore.h> // Additional header for using semaphores

// Barrier definition for molecules
pthread_barrier_t h20_barrier;

// Mutex for oxygen (as we only need one for each molecule)
pthread_mutex_t o_mutex;

// Sempahore for hydrogen (as we will need two for each molecules)
sem_t*  h_sem;

unsigned int num_molecules;

// FUNTION PROTOTYPES
void* h_thread_content(void *arg);
void* o_thread_content(void *arg);

// MAIN FUNCTION
int main(int argc, char const *argv[])
{
    num_molecules = 0;
    
    pthread_mutex_init(&o_mutex, NULL);
    
    sem_t local_sem;
    h_sem = &local_sem;
    sem_init(h_sem, 0, 2);

    pthread_barrier_init(h2o_barrier, NULL, 3);

    pthread_t th[150];

    for(int i=0; i<50; i++)
    {
        if(pthread_create(th + i, NULL, o_thread_content, NULL))
        {
            printf("ERROR... Making O thread was not possible...\n");
            exit(1);
        }
    }
    for(int i=50; i<150; i++)
    {
        if(pthread_create( th + i, NULL, h_thread_content, NULL ))
        {
            printf("ERROR... Making H thread was not possible\n");
            exit(2);
        }
    }

    printf("Now, waiting for reaction of atoms...\n"); 

    for(int i=0; i<150; i++)
    {
        if(pthread_join(th[i], NULL))
        {
            printf("ERROR... Something in the reaction went wrong...\n");
            exit(3);
        }
    }
    printf("There H20 available: %d molecules\n", num_molecules);

    sem_destroy(h_sem);
    
    return 0;
}

// FUNCTION DEFINITIONS

/**
 * Content for hydrogen thread with semaphore.
 * 
 * @param arg Generic pointer to an argument.
*/
void* h_thread_content(void *arg)
{
    sem_wait(h_sem);
    pthread_barrier_wait(&h20_barrier);
    sem_post(h_sem);
    return NULL;
}

/**
 * Content for oxygen thread with mutex and barrier.
 * 
 * @param arg Generic pointer to an argument.
*/
void* o_thread_content(void *arg)
{
    pthread_mutex_lock(&o_mutex);
    pthread_barrier_wait(&h2o_barrier);
    num_molecules++;
    pthread_mutex_unlock(&o_mutex);
}
