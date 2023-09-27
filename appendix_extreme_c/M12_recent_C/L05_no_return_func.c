// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * A function can end with a 'return' or when the '}' is reached (for example, a void 
 * func). But there is space for some optimizations if you specify a no return.
 * 
 * For this rease, C11 added 'no-return' functions which comes with the 'stdnoreturn.h' 
 * header. The implementation is showed below.
 * 
*/

#include <stdnoreturn.h>

_Noreturn void main_no_return()
{
    while(1)
        printf("Hello from a no return function!\n");
}

int main(int argc, char const *argv[])
{
    main_no_return();
    return 0;
}
