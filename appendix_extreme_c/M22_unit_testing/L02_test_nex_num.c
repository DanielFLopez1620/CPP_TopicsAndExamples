// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <assert.h>

#include "L02_fibonacci.h"

/**
 * Test case for checking that number doesn't repeat.
 * 
 * @exception Will assert exception in case of double number.
*/
void TESTCASE_next_number__numbers_should_rotate()
{
    assert(next_number() == 1);
    assert(next_number() == 2);
    assert(next_number() == 3);
    assert(next_number() == 4);
    assert(next_number() == 5);
    assert(next_number() == 6);
}
