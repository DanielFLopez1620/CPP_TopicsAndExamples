// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * C is standardized by ISO and exist a group of people that is in charge of updating C 
 * and making it better. But for this is important to keep in mind some features intact.
 * 
 * One of the most used versions is C11, but there are more recent options like C17. Now,
 * for using a compiler that allows different versions, you need to identify the C version.
 * 
 * Let's look at our version.
 * 
 *      gcc L01_your_c_version.c -o v.out
 *      ./v.out
 * 
 *      gcc L01_your_c_version.c -o v.out -std=c99
 *      ./v.out
*/

int main(int argc, char **argv)
{
#if __STDC_VERSION >= 201710L
    printf("This is the C18 version!");
#elif __STDC_VERSION__ >= 201112L
    printf("This is the C11 version!\n");
#elif __STDC_VERSION__ >= 199901L
    printf("This is the C99 version!\n");
#else
    printf("This is the C89/C90 version!!\n");
#endif
    return 0;
}
