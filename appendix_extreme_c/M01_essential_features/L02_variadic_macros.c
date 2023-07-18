// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang and gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * VARIADIC MACROS: Macros that can accept different number of params.
*/

// Example 1: Custom logging for errors:
#define LOGGING(format, ...) \
    fprintf(stderr, format, __VA_ARGS__)
    // __VA_ARGS__ is an identifier, tells preprocessor to replace with the rest of the params.

// Example 2: Predecessor of "foreach"
#define LOOP_3(X, ...) \
    printf("%s\n", #X);

#define LOOP_3(X, ...) \
    printf("%s\n", #X);

#define LOOP_2(X, ...) \
    printf("%s\n", #X); \
    LOOP_3(__VA_ARGS__)

#define LOOP_1(X, ...) \
    printf("%s\n", #X); \
    LOOP_2(__VA_ARGS__) 
    
#define LOOP(...) \
    LOOP_1(__VA_ARGS__)

int main(int argc, char** argv)
{
    // Validation of number of arguments
    if (argc > 5)
    {
        LOGGING("Too many arguments, max number is five...\n%s\n", __VERSION__);
    }

    // Custom loop
    LOOP(imagine, write, improve)

    return 0;
}
