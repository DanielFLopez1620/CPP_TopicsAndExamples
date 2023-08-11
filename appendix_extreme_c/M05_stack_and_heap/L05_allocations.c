// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang(only for UNIX system)

#include <stdio.h>

/**
 * ALLOCATION: Let's take a look to some commands for allocation:
 * 
 * 'malloc' allocate a memory region by using a pointer and by specifying the size (and type), it 
 * doesn't initialize the allocated memory, it should be done manually after creation.
 * 
 * 'memset' can be used to initialize memory after 'malloc', it should specify the content and the
 * size (and type)
 * 
 * 'realloc' it allocates by resizing an already allocated block. It doesn't modify the data
 * in the old block. If it is not possible to allocate (fragmentation), then it will find the 
 * a one enough, after that it will free the original.
 * 
*/

#include <stdlib.h> // For using memory allocation
#include <string.h> // For using strings and chains

int main(int argc, char **argv)
{
    // Allocation
    char* ptr = (char*)malloc(16*sizeof(char));

    // Initialize and allocate
    memset(ptr, 0, 16 * sizeof(char)); // 0 Definition
    memset(ptr, 0xff, 16 * sizeof(char));  // 0xff Definition

    // Reallocation
    ptr = (char*)realloc( (void*)ptr, 32 * sizeof(char));

    // Free pointer
    free(ptr);
    return 0;
}
