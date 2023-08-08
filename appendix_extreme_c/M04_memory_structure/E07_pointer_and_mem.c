// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>
#include <stdlib.h>


/**
 * Simple function that fills a char array.
 * @param ptr Char pointer for array modification
*/
void content(char* ptr)
{
    ptr[0] = 'D';
    ptr[1] = 'a';
    ptr[2] = 'n';
}

int main(int argc, char** argv)
{
    // Assign memory space with void pointer
    void* void_ptr = malloc(10 *sizeof(char));
    
    // Create char pointer
    char* ptr = (char*)void_ptr;

    // Update and display content
    content(ptr);
    printf("%s!\n", ptr);

    // Pointer managment
    free(ptr);

    return 0;
}