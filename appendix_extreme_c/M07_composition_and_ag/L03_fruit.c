// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <stdio.h>

typedef int bool_t;
struct plant_t;

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

/**
 * Manually allocator for a fruit object.
 * 
 * @return Pointer to the fruit object allocated
*/
fruit_t* fruit_new()
{
    return (fruit_t*) malloc(sizeof(fruit_t));
}

/**
 * Constructor of a fruit object.
 * 
 * @param fruit Pointer to the fruit object you want to construct
*/
fruit_t fruit_ctor(fruit_t* fruit)
{
    fruit->status = SPROUT;
    print("Fruit has appeared\n");
}

/**
 * Destructor of a fruit object
 * 
 * @param fruit Pointer to the fruit object you want to destroy
*/
fruit_t fruit_dtor(fruit_t* fruit) {}

/**
 * Behavior function to get a grown fruit.
 * 
 * @param Pointer to the fruit of interest.
*/
void fruit_grow(fruit_t* fruit)
{
    fruit->status = GROWN;
    print("Fruit has grown\n");
}

/**
 * Behavior function to get a bad fruit after some time.
 * 
 * @param Pointer to the fruit of interest.
*/
void fruit_bye(fruit_t* fruit)
{
    fruit->status = DEAD;
    print("Fruit is bad right now\n");
}