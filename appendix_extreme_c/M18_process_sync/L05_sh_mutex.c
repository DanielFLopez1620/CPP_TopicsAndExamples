// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

// Headers needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

// Inheritance from shared memroy object (father)
#include "L05_sh_mem.h"

// Attributes definition
typedef struct 
{
    struct sh_mem_t* shm;
    pthread_mutex_t* ptr;
} sh_mutex_t;

/**
 * Manually allocate a new shared mutex object.
 * 
 * @return Pointer address of the new object.
*/
sh_mutex_t* sh_mutex_new()
{
    sh_mutex_t* shx = (sh_mutex_t*)malloc(sizeof(sh_mutex_t));
    shx->shm = sh_mem_new();
    return shx;
}

/**
 * Delete properties and pointers of the shared mutex object.
 * 
 * @param shx Pointer of the shared mutex object of interest.
*/
void sh_mutex_delete(sh_mutex_t* shx)
{
    sh_mem_delete(shx->shm);
    free(shx);
}

/**
 * Constructor of the shared mutex object.
 * 
 * @param shx Pointer of the shared mutex object of interest.
 * @param name Name of the mutex.
 * 
 * @exception Launches an error and exits if the mutex's attribute couldn't be initialized.
 * @exception Launches an error and exits if it wasn't possible set the mutex's attribute.
 * @exception Launches an error and exits if it couldn't initialize the mutex.
 * @exception Launches an error and exits if the mutex's attribute isn't destroyed.
*/
void sh_mutex_ctor(sh_mutex_t* shx, const char* name)
{
    sh_mem_ctor(shx->shm, name, sizeof(pthread_mutex_t));
    shx->ptr = (pthread_mutex_t*)sh_mem_getptr(shx->shm);
    
    if(sh_mem_isowner(shx->shm))
    {
        pthread_mutexattr_t mutex_attr;
        int status = -1;
        if((status = pthread_mutexattr_init(shx->shm)))
        {
            fprintf(stderr, "ERROR: Could initialize the mutex %s: %s\n", name, strerror(status));
            exit(1);
        }
        if((status = pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED)))
        {
            fprintf(stderr, "ERROR: Failed to set mutex process (%s) as shared: %s\n", name, strerror(status));
            exit(1);
        }
        if((status = pthread_mutex_init(shx->ptr, &mutex_attr)))
        {
            fprintf(stderr, "ERROR: Mutex %s failed to init: %s\n", name, strerror(status));
            exit(1);
        }
        if((status = pthread_mutexattr_destroy(&mutex_attr)))
        {
            fprintf(stderr, "ERROR: Couldn't destroy mutex attrs (%s): %s\n", name, strerror(status));
            exit(1);
        }
    }
}

/**
 * Destructor of the shared mutex object.
 * 
 * @param shx Pointer to the shared mutex object of interest.
 * 
 * @exception Launches a warn if the mutex cannot be destroyed.
*/
void sh_mutex_dtor(sh_mutex_t* shx)
{
    if (sh_mem_isowner(shx->shm))
    {
        int status = -1;
        if((status = pthread_mutex_destroy(shx->ptr)))
        {
            fprintf(stderr, "WARNING: Couldn't destroy mutex: %s\n", strerror(status));
        }
    }
    sh_mem_dtor(shx->shm);
}

/**
 * Getter of the mutex pointer.
 * 
 * @param shx Pointer to the shared mutex object
 * 
 * @return Mutex pointer
*/
pthread_mutex_t* sh_mutex_getptr(sh_mutex_t* shx)
{
    return shx->ptr;
}

/**
 * Lock control mechanism for the mutex.
 * 
 * @param shx Pointer to the shared mutex object.
 * 
 * @exception Launches an error and exits if it isn't possible to lock the mutex.
*/
void sh_mutex_lock(sh_mutex_t* shx)
{
    int status = -1;
    if ((status = pthread_mutex_lock(shx->ptr)))
    {
        fprintf(stderr, "ERROR: Lock process failed: %s\n", strerror(status));
        exit(1);
    }
}

/**
 * Unlock control mechinsm for the mutex.
 * 
 * @param shx Pointer to the sahred mutex object.
 * 
 * @exception Launches an error and exits if the unlocking fails.
*/
void sh_mutex_unlock(sh_mutex_t* shx)
{
    int status = -1;
    if ((status = pthread_mutex_unlock(shx->ptr)))
    {
        fprintf(stderr, "ERROR: Unlock process failed: %s\n", strerror(status));
        exit(1);
    }
}