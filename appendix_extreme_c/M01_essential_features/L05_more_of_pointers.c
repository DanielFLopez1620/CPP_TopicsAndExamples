// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

#include <stdio.h>

/**
 * GENERIC POINTERS: Refers to thos "void*" pointers, they cannot be dereferenced and
 * they are usually used to hold content of pointers.
 * 
 * DANGLING POINTERS:
*/

void custom_iterator(void* buffer, size_t lenght);
int* num_creator_bad(int value);
int* num_creator_good(int value);

int main(int argc, char** argv)
{
    int num = 1620;
    int* tonum = &num;
    
    // Example 1: Why do not dereference a generic pointer.
    printf("E1: Uncomment the printf ... and you will get an error by a generic pointer...");
    void* genptr = num;
    // printf("%d\n", *genptr);

    // Example 2: Using a generic function.
    printf("\nE2: Using a generic function for memory iteration");
    custom_iterator(&num, sizeof(int));

    // Example 3: The caotic bad error: Segmentation fault
    printf("\nE3: An inexpected pointer error (uncomment to watch)");
    int* otherptr = NULL;
    // otherptr = num_creator_bad(1);
    // printf("%d\nn", *otherptr);

    // Example 4: Usage of pointers (good) to create variables.
    printf("\nE4: Using pointers with malloc and free: ");
    otherptr = num_creator_good(1);
    printf("%d\n", *otherptr);
    free(otherptr);

    printf("\n\n");

    return 0;
}

/**
 * Kind of iteratior that will travel by bytes in the memory to get the content,
 * it uses a void pointer that will be passed as an unsigned char, which is recommended
 * for iteration in range of memories.
 * 
 * @param buffer Generic pointer that store the data pointer.
 * @param lenght Size of the data type.
*/
void custom_iterator(void* buffer, size_t length)
{
    char lim = ' ';
    unsigned char* bufprt = buffer;
    for (size_t i=0; i < length; i++)
    {
        printf("%c 0x%x", lim, *bufprt);
        lim = ',';
        bufprt++;
    }
}

/**
 * Example of a bad function that may lead to crashing the system.
 * 
 * @param value Integer value that will be used in the creation of an integer.
*/
int* num_creator_bad(int value)
{
    int num = value;
    return &num;
}

/**
 * Example of a good function to create a number by using pointers and the heap.
 * 
 * @param value Integer value that will be used in the creation of an integer.
*/
int* num_creator_good(int value)
{
    int* local_ptr = (int*)malloc(sizeof(int));
    *local_ptr = value;
    return local_ptr;
}


