// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * POLYMORPHISM: The idea here is two have the same code for different behaviors, in other words,
 * using the same public interface for  different behaviors.
 * 
 * You can think of it with the movement of a person vs a dog, we can call the function 'walk()' but
 * inside of it is different, as a human has two legs and a dog has four. This is a better approach than
 * using 'dog_walk()' and 'human_walk()'.
 * 
 * The 'why?' polymorphism is that we want to keep the code 'as is' even with different subtypes, so we
 * can keep the same logic and reduce the number of changes, this refers with two key concepts:
 * 
 * - ABSTRACTION:  To have an idea or and unimplemented behavior function that will be defined in the future.
 * - OVERRIDE: To write (under the same name) the parent's implementation with a different behavior in the
 *   child.
 * 
 * Take into account, that for using polymorphsim you will have to create a overrided implementation, and to
 * have a pointer to a variable that will allow the usage of the implementation. So do not forget to check
 * the examples of polymorphism. You can compile them with:
 * 
 *    gcc L05_poly_animal.c -o animal.o
 *    gcc -c L05_poly_animal.c -o animal.o
 *    gcc -c L05_poly_dog.c -o dog.o
 *    gcc -c L05_polymorphism.c -o main.o
 *    gcc animal.o dog.o main.o -o poly.out
 * .  /poly.out
*/

#include <stdlib.h>

// Import public interfaces
#include "L05_poly_animal.h"
#include "L05_poly_dog.h"

int main(int argc, char **argv)
{
    struct animal_t* animal = animal_new();
    struct dog_t* dog = dog_new();

    animal_ctor(animal, "generic", 2);
    dog_ctor(dog);

    animal_walk(animal);
    animal_walk((struct animal_t*)dog);

    animal_dtor(animal);
    dog_dtor(dog);

    free(dog);
    free(animal);
    return 0;
}
