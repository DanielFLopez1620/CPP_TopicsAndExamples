// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang and gcc

#include <stdio.h>

/**
 * POINTER: Strucutre that keeps the direction in memory that can 
 * be used to get, set or copy the value stored in the given direction.
 * 
 * & --> Referencing operator, return the address of a variable next to it.
 * * --> Dereferenci operator, allow indirect access to the memory that
 *       being pointer.
 * 
 * NOTE: Trying to access to a null pointer will crash the system. 
 * 
 * ARITHMETIC: With pointers you can only add (forward) or decrease (backward)
 * as they refere to movements in the memory.
*/

int main( int argc, char** argv)
{
    // Example 1: Basic usage and syntax of a pointer
    printf("\nE1: Usage of pointer...");
    int num = 2; // Variable
    int* ptr_num = 0; // Null pointer 
    ptr_num = &num; // Assign direction
    *ptr_num = 10; // Modify value stored in the direction pointed
    *ptr_num = NULL; // Good practice null pointer
    printf("Var: %d\nPointer: %d", num, *ptr_num);

    // In C++, you use "nullptr" for null pointer

    // Example 2: Arithmetic with pointers.
    printf("\n\nE2: Arithmetic and pointers: ");
    char* letter_ptr = NULL;
    letter_ptr = (char*) &num;
    printf("Before adding: %u\nAfter adding: %u", letter_ptr, letter_ptr+1);

    // Example 3: Using pointer to iterate an array
    printf("\n\nE3: Iterating array...\n");
    int nums[3] = {1, 2 , 3};
    int* ite = &nums[0];
    // It is also possible to use --> int* ite = nums;
    for(;;)
    {
        printf("%d\n", *ite);
        if(ite == &nums[2]) break;
        ite++;
    } 

    return 0;
}