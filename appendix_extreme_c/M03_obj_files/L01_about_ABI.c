// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>

/**
 * API: From Application Programming Interface, for those cases when you want to provide a library, 
 * the consumer should use the provided API, it is the public interface because the rest would be a
 * mistery. Its function is related with the compability of two software components at functional 
 * cooperation.
 * 
 * ABI: From Aplication Binary Interface, it is like an API but in another level. It guarantees the 
 * compatibility of the code at machine-level instructions. Some functions are:
 *      - Validate target architecture.
 *      - Verify existing data types and aligment.
 *      - Validate function calling convention.
 *      - Define how system calls work.
 *      - Name mangling and virtual table layout.
 * The most common standard is 'System V ABI' which main product are the .elf files (from Executable
 * and Linking Format)
 */

int main(int argc, char const **argv)
{
    printf("Hi! Do not forget to review the comments...\n");
    printf("We are talking about ABI (Application Binary Interface)\n");
    
    return 0;
}
