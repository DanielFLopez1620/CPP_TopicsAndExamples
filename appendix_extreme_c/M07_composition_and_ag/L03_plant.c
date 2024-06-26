// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "L03_fruit.h"

// Attribute structure
typedef int bool_t;

typedef struct
{
    int ID;
    struct fruit_t* fruit;
} plant_t;

/**
 * Manually allocator for a plant object.
 * 
 * @return Pointer to the plant object allocated
*/
plant_t* plant_new()
{
    return (plant_t*) malloc (sizeof(plant_t));
}

/**
 * Constructor of a plant object.
 * 
 * @param plant Pointer to the plant object you want to construct
 * @param ID Identificator of the plant
*/
void plant_ctor(plant_t* plant, const int ID)
{
    plant->ID = ID;
    plant->fruit = NULL;
}

/**
 * Destructor of a plant object.
 * 
 * @param plant Pointer to the plant object you want to destroy
*/
void plant_dtor(plant_t* plant)
{
    free(plant->fruit);
}

/**
 * Function to link a fruit that just appeared in the plant.
 * 
 * @param plant Pointer to the plant object you want to link
 * @param fruit Pointer to the plant object you want to link
*/
void plant_appear_fruit(plant_t* plant, struct fruit_t* fruit)
{
    plant->fruit = fruit;
}


/**
 * Function to grow a fruit that is linked to the plant.
 * 
 * @param plant Pointer to the plant object with the fruit of interest
*/
void plant_nutrient_fruit(plant_t* plant)
{
    fruit_grow(plant->fruit);
}

/**
 * Function to take a fruit away of a plant.
 * 
 * @param plant Pointer to the plant object you take away the fruit.
*/
void plant_leave_fruit(plant_t* plant)
{
    fruit_bye(plant->fruit);
    plant->fruit = NULL;
}

/**
 * Behavior function to validate if a plant has a fruit currently.
 * 
 * @param plat Pointer to the plant object of your interest.
 * 
 * @return 1 if has a fruit, 0 otherwise.
*/
bool_t plant_has_fruits(plant_t* plant)
{
    return (plant->fruit != NULL ? 1 : 0);
}