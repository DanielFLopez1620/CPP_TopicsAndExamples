// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <string.h>

// Base declaration of the parent
#include "L02_type1_animal.h"

// Definition of the animal_t attribute structure
#include "L02_type1_animal_p.h"

// Attribute structure
typedef struct
{
    animal_t animal; // Inherit attributes
    unsigned int wingspan;
    unsigned int beak_type;
} bird_t;

/**
 * Manually allocator of a bird object
 * 
 * @return Address for the allocation.
*/
bird_t* bird_new()
{
    return (bird_t*) malloc(sizeof(bird_t));
}

/**
 * Constructor of a bird object.
 * 
 * @param bird Pointer to the bird object to destruct.
*/
void bird_ctor(bird_t* bird,
               const char* species,
               const char* diet ,
               unsigned int wingspan ,
               unsigned int beak_type)
{
    animal_ctor((struct animal_t*)bird, species, diet);
    bird->wingspan = wingspan;
    bird->beak_type = beak_type;
}

/**
 * Destructor of a bird object.
 * 
 * @param bird Pointer to the bird object to destruct.
*/
void bird_dtor(bird_t* bird)
{
    animal_dtor((struct animal_t*) bird);
}

/**
 * Getter of the bird's wingspan.
 * 
 * @param bird Pointer to the bird of interest.
 * 
 * @return Lenght of wingspan in centimeters.
*/
unsigned int bird_get_wingspan(bird_t* bird)
{
    return bird->wingspan;
}

/**
 * Getter of the beak type of a bird object
 * 
 * @param bird Pointer to the bird of interest
 * 
 * @return Number of the beak type
*/
unsigned int bird_get_beak_type(bird_t* bird)
{
    return bird->beak_type;
}