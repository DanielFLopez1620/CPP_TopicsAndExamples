// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * There would be cases when you do not need binary semaphores, so you will need to implement a
 * more general case, or you need to create more threads. So, let's check the example of water
 * molecules.
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h> // Errno and strerror
#include <pthread.h> // POSIX standart header for threads
#include <semaphore.h> // Additional header for using semaphores

pthread_barrier_t h20_barrier;

pthread_mutex_t o_mutex;

sem_t*  h_sem;

unsigned int num_molecules;

void* h_thread_content(void *arg);
void* o_thread_content(void *arg);

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
    
    return 0;
}


void* h_thread_content(void *arg)
{
    sem_wait(h_sem);
    pthread_barrier_wait(&h20_barrier);
    sem_post(h_sem);
    return NULL;
}

void* o_thread_content(void *arg)
{
    pthread_mutex_lock(&o_mutex);
    pthread_barrier_wait(&h2o_barrier);
    num_molecules++;
    pthread_mutex_unlock(&o_mutex);
}
