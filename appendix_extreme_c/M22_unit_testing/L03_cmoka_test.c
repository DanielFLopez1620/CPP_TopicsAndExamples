// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * CMOKA: Written entertyl in C, with only the standard library as a dependency, which allows to do
 * test in a pretty close environment to the actual production, and it works on many platforms, as 
 * you only needd a C compiler.
 * 
 * It is 'de facto' in testing C programs, it offers test fixtures to initialize and clear testing
 * environments before and after each test case. Also functions function mocking (well... this is
 * obvious) and it is very useful, here in this code we will implement a test with this library.
*/

//  Libraries required for Cmocka:

#include <stdarg.h> // Contain a set of macros that allows portable functions that accept variable
                    // args lists to be written.
#include <stddef.h> // Standard type definitions
#include <setjmp.h> // Define array types of jmp_buf and sigjmp_buf
#include <cmoka.h>  // Library for tests

#include "L02_fibonacci.h"

int input_num = -1;

int feed_num()
{
    return input_num;
}

void fibonacci__fib_of_zero_is_zero(void** state)
{
    input_num = 0;
    int result = fibonacci(feed_num);
    assert_int_equal(result, 0);
}

void fibonacci__fib_of_one_is_one(void** state)
{
    input_num = 1;
    int result = fibonacci(feed_num);
    assert_int_equal(result, 1)
}

void fibonnaci__fib_of_four_is_three(void** state)
{
    input_num = 4;
    int result = fibonacci(feed_num);
    assert_int_equal(result, 3);
}

void next_number__numbers_should_rotate()
{
    int num1 = next_number();
    for(int i = 0; i <= 4; i++)
    {
        next_number();
    }
    int num2 = next_number();
    assert_not_equal(num1, num2);
}

int main(int argc, char** argv)
{
    
}