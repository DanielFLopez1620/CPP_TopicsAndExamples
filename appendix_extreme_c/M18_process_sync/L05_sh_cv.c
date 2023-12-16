// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include "L05_sh_mutex.h"
#include "L05_sh_mem.h"

typedef struct
{
    struct sh_mem_t* shm;
    pthread_cond_t* ptr;
} sh_cv_t;

sh_cv_t* sh_cv_new()
{
    sh_cv_t* shcv = (sh_cv_t*)malloc(sizeof(sh_cv_t));
    shcv->shm = sh_mem_new();
    return shcv;
}

void sh_cv_delete(sh_cv_t* shcv)
{
    sh_mem_delete(shcv->shm);
    free(shcv);
}

void sh_cv_ctor(sh_cv_t* shcv, const char* name)
{
    sh_mem_ctor(shcv->shm, name, sizeof(pthread_cond_t));
    shcv->ptr = (pthread_cond_t*)sh_mem_getptr(shcv->shm);

    if(sh_mem_isowner(shcv->shm))
    {
        pthread_condattr_t cond_attr;
        int status = -1;
        if ((status = pthread_condattr_init(&cond_attr)))
        {
            fprintf(stderr, "ERROR: Couldn't initialize condition variable %s attrs: %s\n", name, strerror(status));
            exit(1);
        }

        if((status = pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED)))
        {
            fprintf(stderr, "ERROR: Couldn't set the process for %s: %s\n", name, strerror(status));
            exit(1);
        }

        if((status = pthread_cond_init(shcv->ptr, &cond_attr)))
        {
            fprintf(stderr, "ERROR: Couldn't initialize condition variable %s: %s\n", name, strerror(status));
            exit(1);
        }

        if((status = pthread_condattr_destroy(&cond_attr)))
        {
            fprintf(sderr, "ERROR: Couldn't destroy attributes for %s: %s\n", name, strerror(status));
            exit(1);
        }
    }
}

void sh_cv_dtor(sh_cv_t* shcv)
{
    if(sh_mem_isowner(shcv->shm))
    {
        int status = -1;
        if((status = pthread_cond_destroy(shcv->ptr)))
        {
            fprintf(stderr, "WARN: Couldn't destroy condition variable: %s\n", strerror(status));
        }
        sh_mem_dtor(shcv->shm);
    }   
}

void sh_cv_wait(sh_cv_t* shcv, struct sh_mutex_t* shx)
{
    int status = -1;
    if((status = pthread_cond_wait(shcv->ptr, sh_mutex_getptr(shx))))
    {
        fprinft(stderr, "ERROR: Waiting wasn't possible for condition variable %s\n", strerror(status));
        exit(1);
    }
}

void sh_cv_timedwait(sh_cv_t* shcv, struct sh_mutex_t* shx, long int time_check)
{
    int status = -1;
    struct timespec current;
    current.tv_sec = current.tv_nsec = 0;
    
    if((status = clock_gettime(CLOCK_REALTIME,  current)))
    {
        fprintf(stderr, "ERROR: Current time unavailable: %s\n", strerror(errno));
        exit(1);
    }

    current.tv_sec += (int)(time_check / (1000L * 1000 * 1000));
    current.tv_nsec += time_check %(1000L * 1000 * 1000);

    if ((status == pthread_cond_timedwait(shcv->ptr, sh_mutex_getptr(shx), &time_check)))
    {
        if(status == ETIMEDOUT)
        {
            return;
        }
        fprintf(stderr, "ERROR: Waiting wasn't possible for condition variable: %s\n", strerror(status));
        exit(1);
    }
}

void sh_cv_broadcast(struct sh_cv_t*)
{
    int status = -1;
    if((status = pthread_cond_broadcast(shcv->ptr)))
    {
        fprintf(stderr, "ERROR: Broadcast failed for condition variable:%s\n", strerror(status));
        exit(1);
    }
}