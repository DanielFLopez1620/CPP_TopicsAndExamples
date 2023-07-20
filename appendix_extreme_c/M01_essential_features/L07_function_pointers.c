// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

#include <stdio.h>

/**
 * FUNTION POINTERS: Features that allows modularization and polymorphism. Like a variable
 * pointer addresing a variable, the function pointers address a function. For declaration
 * is mandatory to make the null, also, don not forget to specify the number of params and 
 * its type.
*/

typedef int bool_t;
typedef bool_t (*greater_than_func_t) (int, int);

int multiply(int num1, int num2);
int add(int num1, int num2);
bool_t greater_than(int num1, int num2);
bool_t greater_than_modular(int num1, int num2);

int main(int argc, char const **argv)
{
    int num1 = 2, num2 = 4;
    printf("Numbers in order: %d, %d", num1, num2);
    // Example 1: Using a function pointer...
    printf("E1: Calling a function by a pointer...\n");
    int (*func_ptr)(int, int);
    func_ptr = NULL;
    func_ptr = &multiply;
    printf("\tProduct is: %d", func_ptr(num1, num2));
    func_ptr = &add;
    printf("\t\nSum is: %d\n", func_ptr(num1, num2));

    // Example 2: Using templates...
    printf("\nE2: Using a type alias...\n");
    greater_than_func_t alias_ptr = NULL;
    alias_ptr = &greater_than;
    printf("\tIs num1 greater than num2: %d\n", alias_ptr(num1, num2));
    alias_ptr = &greater_than_modular;
    printf("\tIs num1 greater than num2: %d\n", alias_ptr(num1, num2));
    
    return 0;
}

/**
 * Function that multiplies two numbers.
 * 
 * @param num1 First integer number
 * @param num2 Second integer number
 * 
 * @return Product of the numbers
*/
int multiply(int num1, int num2)
{
    return num1 * num2;
}

/**
 * Function that adds two numbers.
 * 
 * @param num1 First integer number
 * @param num2 Second integer number
 * 
 * @return Sum of the numbers
*/
int add(int num1, int num2)
{
    return num1 + num2;
}

/**
 * Function that logically compares two numbers.
 * 
 * @param num1 First integer number
 * @param num2 Second integer number
 * 
 * @return 1 if first number is greater, 0 otherwise.
*/
bool_t greater_than(int num1, int num2)
{
    return num1 > num2 ? 1: 0;
}

/**
 * Function that modularly compares two numbers.
 * 
 * @param num1 First integer number
 * @param num2 Second integer number
 * 
 * @return 1 if first number is greater, 0 otherwise.
*/
bool_t greater_than_modular(int num1, int num2)
{
    return (num1 % 5) > (num2 % 5) ? 1 : 0;
}

