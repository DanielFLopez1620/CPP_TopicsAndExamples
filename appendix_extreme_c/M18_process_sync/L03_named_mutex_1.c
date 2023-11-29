// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc. 

#include <stdio.h>

/**
 * Mutexes in processes does not work like in the case of threads, and the reason is that you
 * will need a place accessible to all of them, and if you guessed correctly, we will need a 
 * shared memory region.
 * 
 * NOTE: We will use pthread.h as we need  the mutex functions for this.
*/

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>

#define MEM_SIZE 4

// Shared file descriptor to get a shared memory object
int shared_fd = -1;

// Mutex shared file descriptor
int mutex_sh = -1;

// Pointer to the shared resource (in this case a counter)
int32_t* con = NULL;

// Pointer ot mutex implemented
pthread_mutex_t* mt = NULL;

void init_mutex();
void init_mutex()
{
    mutex_sh = shm_open("/mutex0", O_CREAT | O_RDWR, 0600);
    if(mutex_sh < 0)
    {
        fprintf(stderr, "ERROR: Shared memory wasn't created: %s\n", strerror(errno));
        exit(1);
    }

    if (ftruncate(mutex_sh, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Truncation of mutex wasn't completed: %s\n", strerror(errno));
        exit(1);
    }

    void* map = mmap(0, sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE, MAP_SHARED, mutex_sh, 0);

    if(map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping wasn't possible: %s\n", strerror(errno));
        exit(1);
    }

    mt = (pthread_mutex_t*)map;

    int ini = -1;
    pthread_mutexattr_t attr;

    if((ini = pthread_mutexattr_init(&attr)))
    {
        fprintf(stderr, "ERROR: Problem with init attributes: %s\n", strerror(errno));
        exit(1);
    }

    if((ini = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)))
    {
        fprintf(stderr, "ERROR: Problem with setting the attributs: %s\n", strerror(errno));
        exit(1);
    }

    if((ini = pthread_mutex_init(mt, &attr)))
    {
        fprintf(stderr, "ERROR: Initializing mutex wasn't possible: %s\n", strerror(errno));
        exit(1);
    }

    if((ini = pthread_mutexattr_destroy(&attr)))
    {
        fprintf(stderr, "ERROR: Destroying attribute wasn't achieved: %s\n", strerror(errno));
        exit(1);
    }
}

void kill_mutex();
void kill_mutex()
{
    int kll = -1;
}



