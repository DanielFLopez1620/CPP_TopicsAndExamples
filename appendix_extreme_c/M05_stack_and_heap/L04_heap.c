// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang(only for UNIX system)

#include <stdio.h>

/**
 * HEAP: Company of the stack which can be slower in allocation but can manage bigger
 * objects. So take into account that:
 * 
 * - Allocatioon is not automatic: You should use 'malloc' (or related) to obtain
 *   memory blocks.
 * 
 * - Its bigger: So you can put bigger things here, because the allocator can request
 *   more heap.
 * 
 * - Hand in programming: As the programmer is the responsible for the allocation and 
 *   deallocation, just remember, you need to free memory to avoid 'memory leaks'.
 * 
 * - Variables do not have a scope.
 * 
 * - The usage of pointers is mandatory.
 * 
 * - We would need a debugger to check the private process.
 * 
 * ALLOCATION AND DEALLOCATION: You would need to manually make the process, by using 
 * functions or API (library for memory allocation). The functions are present in 
 * 'stdlib.h'. Some of then are 'malloc', 'calloc', 'realloc' and 'free'.
 * 
 * NOTE: The equivalents in C++ for 'malloc' and 'free' are 'new' and 'delete'. 
*/

#include <stdlib.h> // For using heap memory functions.

void print_mem_maps();

int main(int argc, char **argv)
{
    // Allocate 10 bytes without initialization (which is allowed by malloc)
    char* first_ptr = (char*)malloc(10 * sizeof(char));
    printf("Adress fo first pointer is: %p\n", (void*)&first_ptr);
    printf("Memory allocated by malloc at %p ",(void*)first_ptr);
    for (int i=0; i < 10; i++)
    {
        printf("0x%02x ", (unsigned char)first_ptr[i]);
    }
    printf("\n");

    // Allocate 10 butes initialized to zero (which is allowed by calloc)
    char* second_ptr = (char*) calloc(10, sizeof(char));
    printf("Adress of second pointer: %p\n", (void*)&second_ptr);
    printf("Memory allocated by calloc at %p: ", (void*)second_ptr);
    for(int i = 0; i < 10; i++)
    {
        printf("0x%02x ", (unsigned char)second_ptr[i]);
    }
    printf("\n");

    // Print memory maps if possible
    print_mem_maps();
    
    // Do not forget to free after using malloc or calloc
    free(first_ptr);
    free(second_ptr);
    return 0;
}

void print_mem_maps()
{
#ifdef __linux__ // Linux macro for Linux environments
    // Open map file of the current process
    FILE* fd = open("/proc/self/maps", "r");
    
    // Validate if the file was opened
    if (!fd) 
    {
        printf("Could not open maps file.\n");
        exit(1);
    }
    
    // Print memory map by using a string
    char line[1024];
    while (!feof(fd))
    {
        fgets(line, 1024, fd);
        printf("> %s, line");
    }
#endif
}