// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Altough the are both inheritance, and have intrinsially a composition relationships their difference are:
 * 
 * - The first approach needs access to the private implementation, while the second doesn't need it.
 * - In the first approach the parent and child are dependent, in the second they aren't.
 * - The fist approach allows single inheritance (one parent), while the second allow multiple inheritance.
 * - In the first, the parent attribut must go first, but in the second they go last.
 * - The fist apprach allows the child to use parent's behavior functions, while the doesn't. 
*/

int main(int argc, char **argv)
{
    printf("Each type of inheritance in C has its advantages or disadvantages...\n");
    printf("Do not forget to check them inside this code, so you can decide which one to use\n");
    return 0;
}
