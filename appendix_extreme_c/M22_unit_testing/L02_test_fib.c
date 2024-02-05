#include <assert.h>

#include "L02_fibonacci.h"

int consider_value = 0;

/**
 * Function that will feed the fibonacci params, used as a way of simulating the next_num function.
 * 
 * @return The value of the global variable 'consider_value'
*/
int feed_fib()
{
    return consider_value;
}

/**
 * Test case for fibonacci of zero being zero
 * 
 * @exception Will call assertioon if fib of zero is different from zero.
*/
void TESTCASE_fibonacci__fib_of_zero_is_zero()
{
    consider_value = 0;
    int result = fibonaci(consider_value);
    assert(result == 0);
}

/**
 * Test case for fibonacci of one being one
 * 
 * @exception Will call assertioon if fib of one is different from one.
*/
void TESTCASE_fibonacci__fib_of_one_is_one()
{
    consider_value = 1;
    int result = fibonaci(consider_value);
    assert(result == 1);
}

/**
 * Test case for fibonacci of another specific case
 * 
 * @exception Will call assertioon if fib corresponds to value calculated manually.
*/
void TESTCASE_fibonacci__fib_of_four_is_three()
{
    consider_value = 4;
    int result = fibonaci(consider_value);
    assert(result == 3);
}
