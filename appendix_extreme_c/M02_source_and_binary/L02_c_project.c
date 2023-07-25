// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include "L02_c_project.h"

/**
 * HEADER FILES: Those with .h extension. It contains enumarations, macros, prototypes, 
 * typedefs, global variables and structures. They can include other header files, but not
 * source codes.
 * 
 * SOUCER FILES: Those with .c extension. It focus on the development of the variables, 
 * functions and structures so they are defined and search to achieve a purpose.
 * 
 * TIP: For compilation is better to avoid multiple files in one compilation.
 * 
 * NOTE: Having more of one definitions for a declaration will lead to an error.
*/

/**
 * Calculates the sum of all the data given
 * 
 * @param data Pointer to integer array that has all the data.
 * @param size Size of the integer array
 * 
 * @return Sum of the integers stored in data.
*/
int sum(int * data, int size)
{
    int total = 0;
    for(int i=0; i < size; i++)
    {
        total += data[i];
    }
    return total;
}

/**
 * Function that will evaluate the sum (FEW, VALID, MANY, TOO_MANY)
 * 
 * @param sum Sum of the data previously manipulated.
 * 
 * @return Type of the sum.
*/
sum_type_t type_sum(int sum)
{
    if(sum < 10)
        return FEW;
    else if(sum < 20)
        return VALID;
    else if(sum < 30)
        return MANY;
    else
        return TOO_MANY;
}
