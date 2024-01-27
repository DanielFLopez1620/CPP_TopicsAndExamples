/* File name: cstack_tests.c
 * Description: Testing the stack library
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "cstack.h"

/**
 * This a run test example for the code, to check that the stack is working properly in C.
 * For try it, you can run:
 * 
 *    gcc -c -g cstack_tests.c -o tests.o
 *    gcc tests.o -L$PWD -lcstack -o cstack_tests.out
 *    LD_LIBRARY_PATH=$PWD ./cstack_tests.out
 * 
 * If weverything goes right, you should be able to see a message:
 *    
 *    ALL tests were OK
 * 
 * Also, you can check with 'valgrind' to prevent memory leaks.
 * 
 *    LD_LIBRARY_PATH=$PWD valgrind --leak-check=full ./cstack_tests.out
 * 
 * WHEN READY: After you have checked the C codes, it is time to focus on the integration, so go
 * to the C++ implementation.
*/

/**
 * Create a value structure that stores integers.
 * 
 * @param int_value Integer value to store in the future.
 * 
 * @return Value structure with the info provided.
*/
value_t make_int(int int_value) 
{
  value_t value;
  int* int_ptr = (int*)malloc(sizeof(int));
  *int_ptr = int_value;
  value.data = (char*)int_ptr;
  value.len = sizeof(int);
  return value;
}

/**
 * A similar implementation of a getter, that results in obtaining the current value.
 * 
 * @param value Object containing the information of interest.
 * 
 * @return Integer value stored
*/
int extract_int(value_t* value) 
{
  return *((int*)value->data);
}

/**
 * Manual implementation of a deleter to clear the pointers before object destruction.
 * 
 * @param value Pointer to object of interest. 
*/
void deleter(value_t* value) 
{
  if (value->data) 
  {
    free(value->data);
  }
  value->data = NULL;
}

int main(int argc, char** argv) 
{
  // Create a new c stack object
  cstack_t* cstack = cstack_new();
  cstack_ctor(cstack, 100);
  assert(cstack_size(cstack) == 0);

  // Array of future values that will be stored
  int int_values[] = {5, 10, 20, 30};

  // Pass values to the c stack. (push)
  for (size_t i = 0; i < 4; i++) 
  {
    cstack_push(cstack, make_int(int_values[i]));
  }
  assert(cstack_size(cstack) == 4);

  // Obtain values (pop) while optimizing resources
  int counter = 3;
  value_t value;
  while (cstack_size(cstack) > 0) 
  {
    bool_t popped = cstack_pop(cstack, &value);
    assert(popped);
    assert(extract_int(&value) == int_values[counter--]);
    deleter(&value);
  }
  assert(counter == -1);
  assert(cstack_size(cstack) == 0);

  // Push more values and then check
  cstack_push(cstack, make_int(10));
  cstack_push(cstack, make_int(20));
  assert(cstack_size(cstack) == 2);

  // Clear stack
  cstack_clear(cstack, deleter);
  assert(cstack_size(cstack) == 0);

   // In order to have something in the stack while
  // calling destructor.
  cstack_push(cstack, make_int(20));

  // Finally destroy object used
  cstack_dtor(cstack, deleter);
  cstack_delete(cstack);
  printf("All tests were OK.\n");
  return 0;
}
