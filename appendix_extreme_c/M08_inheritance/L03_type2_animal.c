// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <string.h>

typedef struct
{
    char species[20];
    char diet[20];
} animal_t;

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
                 const char* diet)
{
    strcpy(animal->species, species);
    strcpy(animal->diet,diet);
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
 * Getter of the diet of an animal, delivered via pointer to char array.
 * 
 * @param animal Pointer to the animal of interest
 * @param buffer Pointer to load the diet obtained.
*/
void animal_get_diet(animal_t* animal, char* buffer)
{
    strcpy(buffer, animal->diet);
}
