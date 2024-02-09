// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * GOOGLE TEST: It is a testing framework oriented to C++ that can be also used in C programs.
 * As you may suppose, we will need to use the 'extern C' for making sure it will test it for a
 * C program. You can compare the canges between 'L02_fibonacci.c" and "L04_fibonacci_cpp.h" to
 * understand better the idea.
 * 
 * Now, we will focus on the Google Test implementation here, our first steps are going to be
 * the include of the needed libraries. In this case #include <gtest/gtest.h>.
 * 
 * 
*/

#include <gtest/gtest.h>

#include "L04_fibonacci_cpp.h"

int input_num = 0;

int feed_num()
{
    return input_num;
}

TEST(fibonacci, fib_of_zero_is_zero)
{
    input_num = 0;
    int result = fibonacci(feed_num);
    ASSERT_EQ(result, 0);
}

TEST(fibonacci, fib_of_one_is_one)
{
    input_num = 1;
    int result = fibonacci(feed_num);
    ASSERT_EQ(result, 1)
}

TEST(fibonacci, fib_of_four_is_three)
{
    input_num = 4;
    int result = fibonacci(feed_num);
    ASSERT_EQ(result, 3);
}

TEST(next_number, numbers_should_be_rotated)
{
    int num1 = next_number();
    for(int i = 0; i <= 4; i++)
    {
        next_number();
    }
    int num2 = next_number();
    ASSERT_NE(num1, num2);
}