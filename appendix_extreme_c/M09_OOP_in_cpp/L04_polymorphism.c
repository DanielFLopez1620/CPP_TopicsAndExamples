// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// This is mainly a pseudo code, do not try to run it.

#include <stdio.h>

/**
 * Here you can find an approach for using polymorphism with C.
 * 
 * NOTE: Remember that polymorhpic behavior functions are called virtual 
 * (behavior) functions. Non virtual functions aren't polymorphic.
 * 
 * Take into account that C++ uses a similar form, and it uses 'vtable' that
 * is created with the object, which is populated with constructs.
*/

////////////////// PARENT FILE ///////////////////////////////////////
typedef void* (*first_func_t) (void*,...);
typedef void* (*second_func_t) (void*, ...);

typedef struct 
{
    // Attributes
    //...
    // Pointers to functions
    first_func_t func1;
    second_func_t func2;
} pexample_t;

void* __default_first_func(void* pexample, ...) { /* Implementation*/}
void* __default_second_func(void* pexample, ...) { /* Implementation*/}

// Parent constructor
void pexample_gtor(pexample_t* pexample)
{
    // Initialize attributes...
    //...
    // Set functions
    pexample->func1 = __default_first_func;
    pexample->func2 = __default_second_func;
}

////////////////// CHILD FILE ///////////////////////////////////////

// Import all related with the parent

typedef struct 
{
    pexample_t pexample;
    // More attributes...
} cexample_t;

void* __poly_first_func(void* pexample, ...){ /* Override implementation*/}
void* __poly_second_func(void* pexample, ...){ /* Override implementation*/}

void cexample_ctor(cexample_t* cexample)
{
    pexample_ctor((pexample_t*) cexample);
    // Update attributes
    // ...
    cexample->pexample.func1 = __poly_first_func;
    cexample->pexample.func2 = __poly_second_func;
}
