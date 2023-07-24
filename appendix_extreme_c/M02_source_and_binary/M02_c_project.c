// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

/**
 * HEADER FILES: Those with .h extension. It contains enumarations, macros, prototypes, 
 * typedefs, global variables and structures. They can include other header files, but not
 * source codes.
 * 
 * SOUCER FILES: Those with .c extension. It focus on the development of the variables, 
 * functions and structures so they are defined and search to achieve a purpose.
*/

// Example 1: Function declaration, it should be declared in a .h file.
int sum(int*, int);

int main(int argc, char **argv)
{
     
    return 0;
}

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
