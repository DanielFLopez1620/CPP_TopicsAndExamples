// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * Ninja is a faster alternative to Make, but it isn't a replacement.
 * The velocity it gains is added by removing features of CMake and it can be compared with 
 * shell scripting. It removes features related with string manipulation, loops and pattern 
 * matching.
 * 
 * It is not recommended to generate a Ninja file from Scratch, you can use:
 * 
 *      cmake -GNinja <location>
 * 
 * To generate the implementation basing of an already existing CMake implementation you have
 * made. After it is completed, you can run:
 * 
 *      ninja
 * 
*/

int main(int argc, char** argv)
{
    printf("IF you want to learn more of Ninja, you can check:\n");
    printf("\t - https://ninja-build.org/manual.html#_writing_your_own_ninja_files\n");
}