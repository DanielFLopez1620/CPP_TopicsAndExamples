// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * _Generic was an addition oriented to create macros that are type-aware:
*/

#define print_num(x) _Generic((x), \
                               int: print_int, \
                               double: print_dou)(x)
            
void print_int(int x)
{
    printf("%d\n", x);
}

void print_dou(double x)
{
    printf("%f\n", x);
}

int main(int argc, char** argv)
{
    printf("With _Generic, you can create different implementations:\n");
    printf("Printing integer... ");
    print_num(1620);
    printf("Printing decimal... ");
    print_num(16.20);
    return 0;
}