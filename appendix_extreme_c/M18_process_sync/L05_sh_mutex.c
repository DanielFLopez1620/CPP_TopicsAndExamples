// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include "L05_sh_mem.h"

typedef struct 
{
    struct sh_mem_t* shm;
    pthread_mutex_t* ptr;
} sh_mutex_t;

sh_mutex_t* sh_mutex_new()
{
    sh_mutex_t shx = (sh_mutex_t*)malloc(sizeof(sh_mutex_t));
    shx->shm = sh_mem_new();
    return shx;
}

void sh_mutex_delete(sh_mutex_t* shx)
{
    sh_mem_delete(shx->shm);
    free(shx);
}

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
        if((status = pthread_mutexattr_setshared(&mutex_attr, PTHREAD_PROCESS_SHARED)))
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

void sh_mutex_dtor(struct sh_mutex_t*);

pthread_mutex_t* sh_mutex_getptr(struct sh_mutex_t*);

void sh_mutex_lock(struct sh_mutex_t*);
void sh_mutex_unlock(struct sh_mutex_t*);