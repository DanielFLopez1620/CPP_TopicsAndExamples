// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc and g++

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
 * As you will see, here we encapsultate the tests with the TEST(...) macro, there are other like
 * TEST_F and TEST_F that are specific to C++, it works by passsing the original function as the
 * first arg, and the name of the test case as the second arg. And like CMocka, you have 
 * assertions related with equality and inequality.
 * 
 * Finally, you will need to run it, remember that you will need to use gcc and g++ due to Google
 * Test being C++ oriented:
 * 
 *      gcc -g -c L02_fibonacci.c -o impl.o
 *      g++ -std=c++11 -g -c L04_google_test.cpp -o gtests.o
 *      g++ impl.o gtests.o -lgtest -lpthread -o gtest.out
 *      ./gtest.out
 * 
 * NOTE: Try to modify the cases to get the errors, and check how the assertions are show. Also,
 * you may have interest in using the Google Mock library, so check for more info on the internet.
 * 
*/

#include <gtest/gtest.h>

#include "L04_fibonacci_cpp.h"

int input_num = 0;

/**
 * Function that is used to feed the fibonacci, in a safe and replicable way.
 * 
 * @return Integer value of a global variable.
*/
int feed_num()
{
    return input_num;
}

/**
 * Fibonacci test case for zero input, zero output.
 * 
 * @exception Raises error if proposal isn't completed
*/
TEST(fibonacci, fib_of_zero_is_zero)
{
    input_num = 0;
    int result = fibonacci(feed_num());
    ASSERT_EQ(result, 0);
}

/**
 * Fibonacci test case for one input, one output.
 * 
 * @exception Raises error if proposal isn't completed
*/
TEST(fibonacci, fib_of_one_is_one)
{
    input_num = 1;
    int result = fibonacci(feed_num());
    ASSERT_EQ(result, 1);
}

/**
 * Fibonacci test case for four input, three output.
 * 
 * @exception Raises error if proposal isn't completed
*/
TEST(fibonacci, fib_of_four_is_three)
{
    input_num = 4;
    int result = fibonacci(feed_num());
    ASSERT_EQ(result, 3);
}

/**
 * Next num test that validates that numbers are different
 * 
 * @exception Raises error if numbers end up being equal
*/
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

// Run test
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}