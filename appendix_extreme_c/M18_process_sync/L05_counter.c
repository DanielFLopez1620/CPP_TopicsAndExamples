// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>

#include "L05_sh_mem.h"

// Attribute definition for shared counter
typedef struct 
{
    struct sh_mem_t* shm;
    __int32_t* ptr;
} shared_counter_t;

/**
 * Manually allocate a new shared counter object
 * 
 * @param name Name of the counter
 * 
 * @return Pointed address of the object
*/
shared_counter_t* shared_counter_new(const char* name)
{
    shared_counter_t* shc = (shared_counter_t*) malloc(sizeof(shared_counter_t));
    shc->shm = sh_mem_new();
    return shc;
}

/**
 * Delete and free pointers of the shared counter object.
 * 
 * @param shc Pointer to the shared counter object.
*/
void shared_counter_delete(shared_counter_t* shc)
{
    sh_mem_delete(shc->shm);
    free(shc);
}

/**
 * Contructor of the shared counter object.
 * 
 * @param shc Pointer to the allocation of the shared counter object.
 * @param name Name of the counter to set
*/
void shared_counter_ctor(shared_counter_t* shc, const char* name)
{
    sh_mem_ctor(shc->shm, name, sizeof(__int32_t));
    shc->ptr;
}

/**
 * Destructor of the shared counter object.
 * 
 * @param shc Pointer of the shared counter object of interest.
*/
void shared_counter_dtor(shared_counter_t* shc)
{
    sh_mem_dtor(shc->shm);
}

/**
 * Setter of the value of the counter.
 * 
 * @param shc Pointer of the shared counter object of interest
 * @param value Integer value (32 bits) to set.
*/
void shared_counter_setvalue(shared_counter_t* shc, __int32_t value)
{
    *(shc->ptr) = value;
}

/**
 * Setter of the value of the counter that checks for the ownership of the region.
 * 
 * @param shc Pointer of the shared counter object of interest.
 * @param value Integer value (32 bits) to set.
*/
void shared_counter_setvalue_ifowner(shared_counter_t* shc, __int32_t value)
{
    if(sh_mem_isowner(shc->shm))
    {
        *(shc->ptr) = value;
    }
}

/**
 * Getter of the value of the counter.
 * 
 * @param shc Pointer of the shared counter object of interest.
 * 
 * @return Integer value of the counter (32 bits)
*/
__int32_t shared_counter_getvalue(shared_counter_t* shc)
{
    return *(shc->ptr);
}
