// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * ABSTRACTION: Refers to abstract classes, those who can be used to create and object. The reason is
 * because there are not complete. The key of using them is to avoid strong dependencies.
 * 
 * For example, in the world there are many vehicles that need fuel, so for each one (car, boat, tank...)
 * we will need an implementation. So, why not to create a basic usage that wil related with the "refill"
 * interface" so each vehicle has the same but each of them is a different vehicle. So, our abstract
 * class is a 'vehicle' which can trasnport things and need fuel to work.
 * 
 * Always remember this: "Each significan piece of functionality should be implemented in just one
 * place in the source code. Where similar functions are carried out by distinct pieces of code, it is 
 * generally benefical to combine them in one abstraction."
 * 
 * So, do you recall our animal implementation? It should have been better to use it as an abstraction, as
 * we cannot say a generica animal is an "animal", but we can crete different subclasses from this concept.
 * 
 * The polymorphism is key here, as the abstracted classes cannot have a default implementation, in this cases
 * the override is needed to create 'virtual functions'.
 * 
 * You can check a very simple example, in the 'L01_abstracted_interface.c' example. But for a better implementation
 * of an abstraction, you should remove the allocator function from the public interface,
*/

int main(int argc, char **argv)
{
    printf("If you want to know more about abstraction..., you can check:\n");
    printf("\thttps://en.wikipedia.org/wiki/Abstraction_principle_(computer_programming)\n");
    return 0;
}
