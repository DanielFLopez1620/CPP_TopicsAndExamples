// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * AGGREGATION: It also implies an object that contains another object, but the lifetimes are independent.
 * This means, you can cretaed the contained object before the container is constructed. Need an example? 
 * Of course, you can thing about it like a plant and its fruits, the live of the fruits do not depend on
 * the plant, as they can be picked, ate ... but the plant keeps the same, even when the plant dies, the
 * fruit don't "die" at that instant. This example can be run with:
 * 
 *  gcc -c L03_plant.c -o plant.o
 *  gcc -c L03_fruit.c -o fruit.o
 *  gcc -c L03_aggregation.c -o main.o
 *  gcc plant.o fruit.o  main.o  -o exe_agg.out
 *  ./exe_agg.out 
 * 
 * In C the implementation is by linking objects and then specifying the null relationship. But take care
 * with managing object with NULL reference as you can get a segmentation fault error.
 * 
 * Remember that usually there would be more aggregation relationships rather than composition
 * relationships, but they both are 'possession type'. Also, be clear that an aggregation relationship is temporal between objects but not
 * classes.
*/

#include <stdlib.h>
#include "L03_fruit.h"
#include "L03_plant.h"

int main(int argc, char **argv)
{
    // Construct plan
    struct plant_t* plant = plant_new();
    plant_ctor(plant, 1);

    // Construct fruit
    struct fruit_t* fruit = fruit_new();
    fruit_ctor(fruit);

    // Link fruit
    plant_appear_fruit(plant, fruit);

    // Get a grown fruit
    plant_nutrient_fruit(plant);

    // Throw away fruit
    plant_leave_fruit(plant);

    // Fruit is going to die
    fruit_bye(fruit);

    // Free pointers
    plant_dtor(plant);
    free(plant);
    free(fruit);

    return 0;
}
