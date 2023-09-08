// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * APPROACH 1: It generates the inheritance by using private definition of the attribute structure, so the 
 * child can access to the parent attributes only by asking it with the public interface of the parent. So, I
 * encourage you to check the example and see the implementation by using two header files to create the draft
 * of the object and then create a private attribute structure.
 * 
 * You can compile and run the code, with:
 * 
 * gcc -c type1_animal.c -o animal.o
 * gcc -c type1_bird.c -o bird.o
 * gcc -c inheritance_type1.c -o main.o
 * gcc animal.o bird.o main.o -o inh_type1.out
 * ./inh_type1.out
 * 
 * NOTE: In the definition of nested structures, it is important to declare the father structure first,
 * otherwise you lose the possibility of using the fahthers behavior functions.
*/

#include <stdlib.h>

// Add dependencies (headers) of the objects to use
#include "L02_type1_animal.h"
#include "L02_type1_bird.h"


int main(int argc, char** argv)
{
    printf("Example of Inheritance (Approach 1)\n\n");

    struct bird_t* bird = bird_new();
    bird_ctor(bird, "Seagull", "Omnivore", 80, 2);

    struct animal_t* animal = (struct animal_t*) bird;

    char buffer[20];

    animal_get_species(animal, buffer);
    printf("Species: %s\n", buffer);

    animal_get_diet(animal, buffer);
    printf("Diet: %s\n", buffer);

    printf("Wingspan: %d\n", bird_get_wingspan(bird));

    printf("Beak type: %d\n", bird_get_beak_type(bird));

    bird_dtor(bird);
    free(bird);

    return 0;
}
