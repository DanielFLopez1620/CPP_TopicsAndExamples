#ifndef CALC_SERVICE_H
#define CALC_SERVICE_H

/**
 * This service takes care of the real calculation process, and it doesn't use IPC, as it is 
 * defined in the socket programming part. So it means, that this service can be used in a main 
 * function.
 * 
 * Keep in mind, that some calculations won't need a specific context, so you can just have a single
 * service object to handle it (stateless service object). But there is also the possibility that a
 * object would request a previous request then, you will need a unique service object for each
 * client.
 *
 * Now, go to the 'calc_service.c' to understand better the functions implemented.
*/
#include <types.h>

// Calculation status
static const int CALC_SVC_OK = 0;
static const int CALC_SVC_ERROR_DIV_BY_ZERO = -1;

// Forward declaration
struct calc_service_t;

// Memory management function
struct calc_service_t* calc_service_new();
void calc_service_delete(struct calc_service_t*);

// Constructor and destructor
void calc_service_ctor(struct calc_service_t*);
void calc_service_dtor(struct calc_service_t*);

// Methods of the service class
void calc_service_reset_mem(struct calc_service_t*);
double calc_service_get_mem(struct calc_service_t*);
double calc_service_add(struct calc_service_t*, double, double b,
    bool_t mem);
double calc_service_sub(struct calc_service_t*, double, double b,
    bool_t mem);
double calc_service_mul(struct calc_service_t*, double, double b,
    bool_t mem);
int calc_service_div(struct calc_service_t*, double,
        double, double*);

#endif
