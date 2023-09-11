// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "L05_poly_animal.h"
#include "L05_poly_animal_p.h"

// Attribute structure
typedef struct
{
    animal_t animal;
} dog_t;

/**
 * Walking implementation for a dog
 * 
 * @param ptr Pointer to the animal of interest.
*/
void __dog_walk(void* ptr)
{
    animal_t* animal = (animal_t*)ptr;
    for(int i=0; i<animal->num_legs; i++)
    {
        printf("Walking... Moving Leg %d.\n", i);
    }
}

/**
 * Manually allocator for a dog object.
 * 
 * @return Allocated direction of the object.
*/
dog_t* dog_new()
{
    return (dog_t*) malloc(sizeof(dog_t));
}

/**
 * Constructor of a dog object.
 * 
 * @param dog Pointer to the dog to construct.
*/
void dog_ctor(dog_t* dog)
{
    animal_ctor((struct animal_t*)dog, "Puppy", 4);
    dog->animal.walk_func = __dog_walk;
}

/**
 * Constructor of a dog object.
 * 
 * @param dog Pointer to the dog to destroy.
*/
void dog_dtor(dog_t* dog)
{
    animal_dtor((struct animal_t*)dog);
}