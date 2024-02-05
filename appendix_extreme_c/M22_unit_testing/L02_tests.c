#include <stdio.h>

// Test for function next_number
void TESTCASE_next_number__numbers_should_rotate();

// Test for fibonacci function
void TESTCASE_fibonacci__fib_of_zero_is_zero();
void TESTCASE_fibonacci__fib_of_one_is_one();
void TESTCASE_fibonacci__fib_of_four_is_three();

// Main for running the tests
int main(int argc, char** argv)
{
    TESTCASE_next_number__numbers_should_rotate();
    TESTCASE_fibonacci__fib_of_zero_is_zero();
    TESTCASE_fibonacci__fib_of_one_is_one();
    TESTCASE_fibonacci__fib_of_four_is_three();

    // If one test fails, the print won't be reached and will return a value different from zero.
    printf("All the test were passed\n");
    return 0;
}