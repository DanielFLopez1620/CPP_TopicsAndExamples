/* File name: cstack.c
 * Description: Definitions of the stack library
 */

#include <stdlib.h>
#include <assert.h>

#include "cstack.h"

// Stack attributes definition (for encapsulation)
struct cstack_type  
{
  size_t top;       // Current value of position (in size) of the stack
  size_t max_size;  // Max size of the stack
  value_t* values;  // Pointer to values stored inside of the stack
};

/**
 * Copy the given information to structure for future management fo data in the Stack.
 * 
 * @param data Pointer to char array with the info to copy
 * @param len Size of the data
 * 
 * @return Value structure for future stack operations
*/
value_t copy_value(char* data, size_t len) 
{
  // Create a buffer to allocate the data
  char* buf = (char*)malloc(len * sizeof(char));

  // Update the content of the buffer
  for (size_t i = 0; i < len; i++) 
  {
    buf[i] = data[i];
  }

  // Create value structure and return
  return make_value(buf, len);
}

/**
 * Create a structure of value that relates the content and the size
 * 
 * @param data Char pointer to array that contians the information
 * @param len Lengh of the data (char array)
 * 
 * @return Value structure for future stack operations
*/
value_t make_value(char* data, size_t len) 
{
  value_t value;
  value.data = data;
  value.len = len;
  return value;
}

/**
 * Make sure ot free the pointer and assing null value ot prevent memory usage errors.
 * 
 * @param value Pointer to object to free
*/
void free_value(value_t* value) 
{
  if (value) 
  {
    if (value->data) 
    {
      free(value->data);
      value->data = NULL;
    }
  }
}

/**
 * Manually allocate a custom c stack object in memory.
 * 
 * @return Adress of the allocated of the object.
*/
cstack_t* cstack_new() 
{
  return (cstack_t*)malloc(sizeof(cstack_t));
}

/**
 * Free memory of custom c stack object
 * 
 * @param stack Pointer to cstack object to delete.
*/
void cstack_delete(cstack_t* stack) 
{
  free(stack);
}

/**
 * Constructor of custom c stack object
 * 
 * @param cstack Pointer to allocated object
 * @param max_size Limit size stimated for the info stored in the object.
*/
void cstack_ctor(cstack_t* cstack, size_t max_size) 
{
  cstack->top = 0;
  cstack->max_size = max_size;
  cstack->values = (value_t*)malloc(max_size * sizeof(value_t));
}

/**
 * Destructor of custom c stack object
 * 
 * @param cstack Pointer to c stack object of interest.
 * @param deleter Pointer to function for deleting of value present in the stack.
*/
void cstack_dtor(cstack_t* cstack, deleter_t deleter) 
{
  cstack_clear(cstack, deleter);
  free(cstack->values);
}

/**
 * Getter of the size of the stack
 * 
 * @return Top or limit size of the stack object.
*/
size_t cstack_size(const cstack_t* cstack) 
{
  return cstack->top;
}

/**
 * Interface to push (put a value) in the stack
 * 
 * @param cstack Pointer to stack object
 * @param value Object that has the information to push.
 * 
 * @return TRUE if operation is a success, FALSE otherwise
*/
bool_t cstack_push(cstack_t* cstack, value_t value) 
{
  if (cstack->top < cstack->max_size) 
  {
    cstack->values[cstack->top++] = value;
    return TRUE;
  }
  return FALSE;
}

/**
 * Interface to pop (take out a value) in the stack
 * 
 * @param cstack Pointer to stack object.
 * @param value Pointer to object where the value is going to be popped out.
 * 
 * @return TRUE if the operation was succesful, FALSE otherwise
*/
bool_t cstack_pop(cstack_t* cstack, value_t* value) 
{
  if (cstack->top > 0) 
  {
    *value = cstack->values[--cstack->top];
    return TRUE;
  }
  return FALSE;
}

/**
 * Total clean of the stack (delete all info present)
 * 
 * @param cstack Pointer to object to clean
 * @param deleter Pointer to function that will be used to deletion.
 * 
 * @exception Will raise error in case a value isn't popped oust.
*/
void cstack_clear(cstack_t* cstack, deleter_t deleter) 
{
  value_t value;
  while (cstack_size(cstack) > 0) 
  {
    bool_t popped = cstack_pop(cstack, &value);
    assert(popped);
    if (deleter) 
    {
      deleter(&value);
    }
  }
}
