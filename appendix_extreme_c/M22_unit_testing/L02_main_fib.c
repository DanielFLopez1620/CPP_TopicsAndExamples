#include <stdio.h>

#include "L02_fibonacci.h"

/**
 * For executing this code, you can use:
 *      gcc -c L02_fibonacci.c -o impl.o
 *      gcc -c L02_main_fib.c -o main.o
 *      gcc impl.o main.o -o fib.out
*/

int main(int argc, char** argv)
{
    for(int i = 0; i < 10; i++)
    {
        printf("Fibonacci of %d is %d.\n", i, fibonaci(i));
    }
    return 0;
}