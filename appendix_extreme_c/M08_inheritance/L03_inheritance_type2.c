// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * APPROACH 2: Instaed of nesting structures, you can add a pointer to the parent structure which creates
 * the possibility of independent usage of the structures. This implies that the pointers are no longer
 * interchangeable as they are pointing to different adresses, also you will need to reimplement the parent
 * behavior functions in order to interact with the attributes of the parent.
 * 
 * Do not forget to pass and check the codes, you can run them by:
 * ...
 * 
 * NOTE: Each approach hast its own advantages and disadvantages, they are covered in the next lesson.
*/

#include <stdlib.h>

#include "L03_type2_bird.h"

int main(int argc, char **argv)
{
    struct bird_t* bird = bird_new();
    bird_ctor(bird, "Peacock", "Herbivore", 150, 1);

    char buffer[20];

    bird_get_species(animal, buffer);
    printf("Species: %s\n", buffer);

    bird_get_diet(animal, buffer);
    printf("Diet: %s\n", buffer);

    printf("Wingspan: %d\n", bird_get_wingspan(bird));

    printf("Beak type: %d\n", bird_get_beak_type(bird));

    bird_dtor(bird);
    free(bird);
        
    return 0;
}
