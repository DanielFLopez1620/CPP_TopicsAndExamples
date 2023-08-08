// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <unistd.h> // For sleep function
#include <stdlib.h> // For malloc function
#include <stdio.h>  // Standart input/output

int main()
{
    void* ptr = malloc(1024); // Manually allocate 1 KB from heap
    printf("Adress: %p\n", ptr); 
    fflush(stdout); // Force the print
    while(1)
    {
        sleep(1); // Sleep one second
    }
    return 0;
}