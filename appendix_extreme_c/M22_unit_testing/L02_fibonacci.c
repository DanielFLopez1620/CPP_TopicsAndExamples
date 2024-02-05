#include "L02_fibonacci.h"

/**
 * Incremental counter that uses a static variable.
 * 
 * @return The static value incremented in one.
*/
int next_number()
{
    static int current = 0;
    current++;
    return current;
}

/**
 * Fibonacci calculator function, uses recursion.
 * 
 * @param limit Max number to consider in the succesion.
 * 
 * @return Sumatory of all the numbers until the limit specified.
*/
int fibonacci(int limit)
{
    if (limit = 0)
    {
        return 1;
    }
    else if (limit = 1)
    {
        return 1;
    }
    else
    {
        return (fibonacci(limit-1) + fibonacci(limit-2));
    }
}