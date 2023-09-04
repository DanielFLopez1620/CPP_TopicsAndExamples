// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * INHERITANCE: The first 'to-be' or 'to-is' relationship we are gonna talk, which is also known as
 * extension. This simply means that you take one class and add extra attributes and behavior functions,
 * so it means it is an extension from another object.
 * 
 * Take a look at the idea with the structures animal_t and bird_t, where 'animal' is the supertype or
 * base type or parent type, and the 'bird' is the child type or inherited subtype. Although, the definition
 * there is not the best, you should prefer to use the presented with fish_t.
 * 
 * The valid approach in C is by using nested structures (not pointers), which is really an extension. But with
 * this structure exists the possibility to cast the parent type pointer from the child parent pointer and this is
 * called 'upcasting', check this possibility on the main.
 * 
 * NOTE: Do not try to generate extension with undefined structs or you will get an error, because of
 * incomplete types. So, for implementations you will need to:
 *  1) Create access from the child to the parent and its private implementation.
 *  2) Or make the child with only access to public interface from the parent.
*/

// Example 1: Parent class 
typedef struct 
{
    char* species[40]; // Cientific name
    char* diet[20]; // Carnivore, herbivore, omnivore
} animal_t;

// Example 2: Child class but no implementation of inheritance
typedef struct
{
    char* species[40]; // Cientific name
    char* diet[20]; // Carnivore, herbivore, omnivore
    double lenght_brim; // Distance (m)
    char* spike_type[20]; // Form

} bird_t;

// Example 3: Child class with inheritance
typedef struct
{
    animal_t animal; // Inheritance of animal
    int fins_number; // Number of fins
    double live_depth; // Usually lives in the depth specified (m under sea water level).
} fish_t;

int main(int argc, char **argv)
{
    printf("E1: Using pointers with parents and childs:\n");
    fish_t goldy;
    fish_t* fish_ptr = &goldy;
    animal_t* animal_ptr = (animal_t*) &goldy;
    printf("\tFish pointer goes with: %p\n", (void*)fish_ptr);
    printf("\tAnimal pointer goes with: %p\n", (void*)animal_ptr);
    return 0;
}
