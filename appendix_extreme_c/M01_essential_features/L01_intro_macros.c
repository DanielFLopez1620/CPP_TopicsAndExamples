// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

#include <stdio.h>
#include <string.h>

/**
 * MACRO: Tool for improving preprocessing by defining constants, implementing funcitons
 * create loops or headers, and conditional compilation that are related with the 
 * #define directive. They only exist before the compilation.
 * 
 * NOTE:Precompilation with clang uses: clang -E <c_code>.c
*/

// Macro used as a constant definition
#define MY_MACRO 1620
#define PRINT(inte) printf("%d\n, inte");

// Macro used to define a "function"
#define SUBSTRACT(n1, n2) n1 + n2

// A Macro can be used with multiline by adding "\" at the end of the command.
#define MPRINT(n1) \
    printf("%d\n", n1); \
    printf("%d\n", n1*2);

// The "#" symbol have other uses, for example, after using a varible and adding it
// with a single call (#var) it refers to copy or if you use "##" it is concatenation.
#define MANCP(LETTER) \
    char LETTER ## _group[2] = "";\
    strcpy(LETTER ## _group, #LETTER); \
    printf("%s\n", LETTER ## _group);

int main()
{
    int x = MY_MACRO;
    int y = x*2;
    int z = SUBSTRACT(x,y);
    PRINT(z);
    MANCP(op);
    return 0;
}