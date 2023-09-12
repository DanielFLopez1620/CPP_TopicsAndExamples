// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "L05_poly_animal_p.h"

/**
 * Default definition of an animal moving (walking) needed for future polymorphism
 * 
 * @param this_ptr Pointer of the animal of interest
*/
void __animal_walk(void* this_ptr)
{
    animal_t* animal = (animal_t*)this_ptr;
    printf("Animal is walking...\n");
}

/**
 * Manually allocation for animal objects 
 * 
 * @return Allocation for the object.
*/
animal_t* animal_new()
{
    return (animal_t*) malloc(sizeof(animal_t));
}

/**
 * Constructor of an animal object.
 * 
 * @param animal Pointer to the animal to construct
 * @param species Cientific or common name of the animal
 * @param diet If the animal is carnivore, herbivore...
*/
void animal_ctor(animal_t* animal,
                 const char* species,
                 int num_legs)
{
    strcpy(animal->species, species);
    animal->num_legs = num_legs;
    animal->walk_func = __animal_walk;
}

/**
 * Destructor fo an animal object.
 * 
 * @param animal Pointer to the animal to destruct
*/
void animal_dtor(animal_t animal) {}


/**
 * Getter of the species of an animal, delivered via pointer to char array.
 * 
 * @param animal Pointer to the animal of interest
 * @param buffer Pointer to load the species obtained.
*/
void animal_get_species(animal_t* animal, char* buffer)
{
    strcpy(buffer, animal->species);
}

/**
 * Beahivor function to make the animal move
 * 
 * @param animal Pointer of the desired animal to interact
*/
void animal_walk(animal_t* animal)
{
    animal->walk_func(animal);
}
