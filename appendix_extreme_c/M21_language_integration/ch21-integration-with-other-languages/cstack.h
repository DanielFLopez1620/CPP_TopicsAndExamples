/* 
 * File name: cstack.h
 * Description: Declarations of the stack library
 * 
 * NOTE: It is called cstack to avoid confussion with the stack itsefl.
*/

/**
 * Here are the definition of a custom c stack that will serve as a base for a library that is
 * going to be used with other codes from different languages.
 * 
 * Do not forget to also check the implementation of the OOP in the 'cstack.c' file.
 * 
 * When compiling and creating the library, you need to be located in the root of the project
 * (ch21-integration-with-other-languages). Then run the next commands:
 * 
 *    gcc -c -g -fPIC cstack.c -o cstack.o
 *    gcc -shared cstack.o -o libcstack.so
 * 
 * WHEN READY: Go to the file 'cstack_tests.c'
*/
#ifndef _CSTACK_H_
#define _CSTACK_H_

#include <unistd.h>

#ifdef __cplusplus
extern "C" 
{
  #endif

  #define TRUE 1
  #define FALSE 0

  typedef int bool_t;

  // Struct definition to handle data with this length
  typedef struct 
  {
    char* data;
    size_t len;
  } value_t;

  typedef struct cstack_type cstack_t;

  // Custom type of deleter_t function that needs a value and return a generic pointer
  typedef void (*deleter_t)(value_t* value);

  value_t make_value(char* data, size_t len);
  value_t copy_value(char* data, size_t len);
  void free_value(value_t* value);

  // Memory management for object
  cstack_t* cstack_new();
  void cstack_delete(cstack_t*);

  // Behavior functions (constructor and destructor)
  void cstack_ctor(cstack_t*, size_t);
  void cstack_dtor(cstack_t*, deleter_t);

  // Stack class methods
  size_t cstack_size(const cstack_t*);
  bool_t cstack_push(cstack_t*, value_t value);
  bool_t cstack_pop(cstack_t*, value_t* value);
  void cstack_clear(cstack_t*, deleter_t);

  #ifdef __cplusplus
}
#endif

#endif
