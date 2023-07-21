// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

#include <stdio.h>

/**
 * STRUCTURES: A step toward encapsulation that C took. It allows to create new types.
 * For definition you use < struct <name> { ... };
 * Each local variable is an attribute you will need to instance separately by dot accesing.
 *      <struct>.<attribute> = <value>;
 * If it is a pointer to a struct, you need to use the arrow operator '->':
 *      <struct_pointer>-><attribute> = <value>;
 * 
 * NOTE: For new datatypes a good practice is to add "_t" at the end of the name.
*/

// Example 1: Structure to know the number of fruits.
struct fruits_t
{
    int apple;
    int banana;
    int pear;
};

void get_size(struct fruits_t* basket);
void get_bytes(struct fruits_t* basket);

int main(int argc, char **argv)
{
    // Example 2: Using a structure.
    printf("E2: Usage of a structure");
    struct fruits_t your_basket;

    your_basket.apple = 2;
    your_basket.banana = 3;
    your_basket.pear = 1;
    get_size(&your_basket);
    get_bytes(&your_basket);

    return 0;
}

/**
 * Print the size of the structure by pointer
 * 
 * @param basket Pointer to the structure
*/
void get_size(struct fruits_t* basket)
{
    printf("Size: %lu bytes\n", sizeof(*basket));
}

/**
 * Print the bytes info of the structure by pointer
 * 
 * @param basket Pointer to the structure
*/
void get_bytes(struct fruits_t* basket)
{
    int* ind = (int*) basket;
    printf("\nBytes: ");
    for(int i = 0; i < sizeof(*basket); i++, ind++)
    {
        printf("%d ", (unsigned int)*ind);
    }
    printf("\n");

}