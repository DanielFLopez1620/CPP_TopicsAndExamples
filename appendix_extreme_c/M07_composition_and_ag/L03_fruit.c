// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>

typedef int bool_t;

typedef enum
{
    SPROUT,
    GROWN,
    DEAD
} fstatus_t;

typedef struct
{
    fstatus_t status;
} fruit_t;

fruit_t* fruit_new()
{
    return (fruit_t*) malloc(sizeof(fruit_t));
}

fruit_t fruit_ctor(fruit_t* fruit)
{
    fruit->status = SPROUT;
}

fruit_t fruit_dtor(fruit_t* fruit) {}

bool_t plant_has_fruits