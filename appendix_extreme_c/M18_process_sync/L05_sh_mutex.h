// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <pthread.h>

// Struct and types definition
struct sh_mutex_t;

// Prototypes
struct sh_mutex_t* sh_mutex_new();
void sh_mutex_delete(struct sh_mutex_t*);

void sh_mutex_ctor(struct sh_mutex_t*, const char*);

void sh_mutex_dtor(struct sh_mutex_t*);

pthread_mutex_t* sh_mutex_getptr(struct sh_mutex_t*);

void sh_mutex_lock(struct sh_mutex_t*);
void sh_mutex_unlock(struct sh_mutex_t*);
