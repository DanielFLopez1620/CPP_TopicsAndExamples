// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include "L05_sh_mutex.h"
#include "L05_sh_mem.h"

// Ttribute struc definition
typedef struct
{
    struct sh_mem_t* shm;
    pthread_cond_t* ptr;
} sh_cv_t;

/**
 * Manually allocate a new region for a shared condition variable object
 * 
 * @return Adress to allocate the object.
*/
sh_cv_t* sh_cv_new()
{
    sh_cv_t* shcv = (sh_cv_t*)malloc(sizeof(sh_cv_t));
    shcv->shm = sh_mem_new();
    return shcv;
}

/**
 * Destroy and clear shared condition variable object.
 * 
 * @param shcv POinter to the shared condition variable object of interest.
*/
void sh_cv_delete(sh_cv_t* shcv)
{
    sh_mem_delete(shcv->shm);
    free(shcv);
}

/**
 * Constructor of a shared condition variable object.
 * 
 * @param shcv Adress to initialize the object.
 * @param name Name of the shared resource.
 * 
 * @exception Launches an error and exits if the attributes for the cv couldn't be initialized.
 * @exception Launches an error and exits if the attributes for the cv aren't set.
 * @exception Launches an error and exits if the cv isn't initialized.
 * @exception Launches an error and exits if the attributes cannot be destroyed.
 * 
*/
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

/**
 * Destructor of a shared condition variable object.
 * 
 * @param shcv POinter to the shared cv object of interest.
 * 
 * @exceptionLaunches a arn if the condition variable couldn't be destroyed.
*/
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

/**
 * Waiting operation for a condition variable that was successfuly set.
 * 
 * @param shcv Pointer to the shared condition variable object of interest.
 * @param shx Pointer to the shared mutex object, which gives the control mechanism.
 * 
 * @exception LAunches and error and exits if the wait operation fails. 
*/
void sh_cv_wait(sh_cv_t* shcv, struct sh_mutex_t* shx)
{
    int status = -1;
    if((status = pthread_cond_wait(shcv->ptr, sh_mutex_getptr(shx))))
    {
        fprinft(stderr, "ERROR: Waiting wasn't possible for condition variable %s\n", strerror(status));
        exit(1);
    }
}

/**
 * Waiting operation plus timer for a condition variable.
 * 
 * @param shcv Pointer to the shared condition variable object of interest.
 * @param shx Pointer to the shared mutex object, which gives the control mechanism.
 * @param time_check Time passed in nanoseconds.
 * 
*/
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

/**
 * Broadcaster for shared condition variable object
 * 
 * @param shcv Pointer to the shared condition variable object of interest.
 * 
 * @exception Launches an error and exits if the broadcast isn't achieved with success.
*/
void sh_cv_broadcast(sh_cv_t* shcv)
{
    int status = -1;
    if((status = pthread_cond_broadcast(shcv->ptr)))
    {
        fprintf(stderr, "ERROR: Broadcast failed for condition variable:%s\n", strerror(status));
        exit(1);
    }
}