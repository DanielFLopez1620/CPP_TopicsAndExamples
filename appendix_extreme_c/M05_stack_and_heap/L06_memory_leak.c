// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc (This code is intended to fails)


#include <stdio.h>

/**
 * TESTING MEMORY LEAKS: As you already know, they happen when allocated memory is not
 * freed. Sometimes, this can be difficult to see, for that exists one tool called 'valgrind'.
 * To use this option the compilation should include the debug flag (-g), then the execution
 * should be made with valgrind:
 * 
 *     gcc -g <c_code>.c -o <file>.out
 *     valgrind ./<file>.out
 * 
 * For this code, the output is:
 * 
 *     ==2953== Memcheck, a memory error detector
 *     ==2953== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
 *     ==2953== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
 *     ==2953== Command: ./leak.out
 *     ==2953== 
 *     This program will create a memory leak...==2953== 
 *     ==2953== HEAP SUMMARY:
 *     ==2953==     in use at exit: 16 bytes in 1 blocks
 *     ==2953==   total heap usage: 2 allocs, 1 frees, 1,040 bytes allocated
 *     ==2953== 
 *     ==2953== LEAK SUMMARY:
 *     ==2953==    definitely lost: 16 bytes in 1 blocks
 *     ==2953==    indirectly lost: 0 bytes in 0 blocks
 *     ==2953==      possibly lost: 0 bytes in 0 blocks
 *     ==2953==    still reachable: 0 bytes in 0 blocks
 *     ==2953==         suppressed: 0 bytes in 0 blocks
 *     ==2953== Rerun with --leak-check=full to see details of leaked memory
 *     ==2953== 
 *     ==2953== For lists of detected and suppressed errors, rerun with: -s
 *     ==2953== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
 * 
 * Even, you can make a better check with the option --leak-check=full
 *     valgrind --leak-check=full ./<file>.out
 * 
 * Some alternatives for valgrind are LLVM Adress Sanitizer or MemProf.
 * 
 * NOTE: If you do not have valgrind, you can run in debian systems:
 *      sudo apt install valgrind
*/

#include <stdlib.h> // For using allocation functions

int main(int argc, char **argv)
{
    printf("This program will create a memory leak...");

    // This pointer will not be freed, creating a memory leak.
    char* ptr = (char*) malloc(16 * sizeof(char));

    // Uncomment the next line to solve the memory leak
    // free(ptr);
    return 0;
}
