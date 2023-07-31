#include "L03_relocatable.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int min_3(int a, int b, int c)
{
    int temp = min(a, b);
    return c < temp ? c : temp; 
}