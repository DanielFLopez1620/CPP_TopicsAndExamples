#include <assert.h>

#include "L02_fibonacci.h"

int consider_value = 0;

int feed_fib()
{
    return consider_value;
}

void TESTCASE_fibonacci__fib_of_zero_is_zero()
{
    consider_value = 0;
    int result = fibonaci(consider_value);
    assert(result == 0);
}

void TESTCASE_fibonacci__fib_of_one_is_one()
{
    consider_value = 1;
    int result = fibonaci(consider_value);
    assert(result == 1);
}
