// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>

// Enumaration for status of the class
typedef enum {GROUND, AERIAL, ACUATIC} movement_t;

// Function pointer type
typedef movement_t (*get_movement_t)(void*);

typedef struct 
{
    char name[20];
    get_movement_t movement_func;
    float fuel;
} vehicle_t;

/**
 * Manually allocator of a vehicle type
 * 
 * @return Allocation of the vehicle in memory
*/
vehicle_t* vehicle_new()
{
    return (vehicle_t*) malloc(sizeof(vehicle_t));
}

/**
 * Simple constructor of an abstraccted class, for future virtual functions.
 * 
 * @param vehicle Generic vehicle pointer of interest
*/
void vehicle_ctor(vehicle_t* vehicle)
{
    vehicle->movement_func = NULL;
}

