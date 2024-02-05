#include "L02_fibonacci.h"

int next_number()
{
    static int current = 0;
    current++;
    return current;
}

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