// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc (This code is intended to fails)

#include <stdio.h>

/**
 * Key concept, the programmer is the unique person that know the lifetime of a variable in
 * the Heap region, and for that is the responsible for the deallocation.
 * 
 * One strategy for this is using owners for memory blocks instead of having a scope
 * that relates with a block. This is also called ownership.
*/

typedef struct 
{
    int num1;
    int num2;
    float* com1;
} complex_t;


int main(int argc, char **argv)
{
     
    return 0;
}
