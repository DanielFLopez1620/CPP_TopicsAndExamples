// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang and gcc

#include <stdio.h>

/**
 * CONDITIONAL COMPILATION: It refers to conditions interpreted in the preprocessing phase that will
 * impact the compilation. The usage is related with #ifdef, #ifndef, #else, #elif, #endif.
 * 
 * NOTE: Macros can be passed in compilation by adding -D, useful for trying different archs.
 *     $ gcc -D<condition> -E <c_code>.c
 * 
 * ANOTHER NOTE: You can prevent double inclusion with #ifndef or #pragma, but only in
 * cases where portability is not a requirement.
*/

// Example 1: Using define to create a condition.
#define PASS

// Example 2: Adding a macro if it's present.
#ifndef STEP
    #define STEP 1
#endif


int main(int argc, char const **argv)
{
    // Encapsuled code with macro condition
#ifdef PASS
    printf("Entry was passed...");
#endif
    printf("Continue with code...");

    // Usage of macro in print
    printf(STEP);
    return 0;
}

