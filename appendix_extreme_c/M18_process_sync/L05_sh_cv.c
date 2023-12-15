// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include "L05_sh_mutex.h"
#include "L05_sh_mem.h"

typedef struct
{
    struct sh_mem_t* shm;
    pthread_cond_t* ptr;
} sh_cv_t;

struct sh_cv_t* sh_cv_new();

void sh_cv_delete(struct sh_cv_t*);

void sh_cv_ctor(struct sh_cv_t, const char*);

void sh_cv_dtor(struct sh_cv_t*);

void sh_cv_wait(struct sh_cv_t*, struct sh_mutex_t*);

void sh_cv_timedwait(struct sh_cv_t*, struct sh_mutex_t*, long int);

void sh_cv_broadcast(struct sh_cv_t*);