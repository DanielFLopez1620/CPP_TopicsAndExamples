#include <stdlib.h>

#include "calc_service.h"

/**
 * When you are ready and understand this part, you can go to the part that talks about unix domain
 * sockets, the first file to check is: ""
*/

// Attribute structure for the service
struct calc_service_t 
{
  double mem;
};

/**
 * Manually allocate a new service object.
 * 
 * @return Adress of the allocated object by a pointer
*/
struct calc_service_t* calc_service_new() 
{
  return (struct calc_service_t*)malloc(sizeof(struct calc_service_t));
}

/**
 * Delete service object and free memory
 * 
 * @param svc Pointer to service object in use.
*/
void calc_service_delete(struct calc_service_t* svc) 
{
  free(svc);
}

/**
 * Constructor of service object that only initialize memory value with zero
 * 
 * @param svc Pointer to service object in use
*/
void calc_service_ctor(struct calc_service_t* svc) 
{
  svc->mem = 0.0;
}

/**
 * Void constructor for service objects.
 * 
 * @param svc Pointer to service object in use
*/
void calc_service_dtor(struct calc_service_t* svc) {}

/**
 * Reset memory (upate to zero)
 * 
 * @param svc Pointer to service object in use
*/
void calc_service_reset_mem(struct calc_service_t* svc) 
{
  svc->mem = 0.0;
}

/**
 * Getter to value stored in memory
 * 
 * @param svc Pointer to service object in use
 * 
 * @return Double value currently stored in object.
*/
double calc_service_get_mem(struct calc_service_t* svc) 
{
  return svc->mem;
}

/**
 * Addition function that has two option: Add two numbers or additionally add value
 * stored in memory.
 * 
 * @param svc Pointer to service object in use
 * @param a Operand 1
 * @param b Operand 2
 * @param mem Boolean that indicates if stored value is added
 * 
 * @return Sum according the operands passed
*/
double calc_service_add(struct calc_service_t* svc, double a, double b,
    bool_t mem) 
{
  double result = a + b;
  if (!mem) 
  {
    return result;
  }
  svc->mem = result + svc->mem;
  return svc->mem;
}

/**
 * Substraction function that has two options: Substraction between two operands or
 * additionally consider memory.
 * 
 * @param svc Pointer to service object in use
 * @param a Operand 1
 * @param b Operand 2
 * @param mem Boolean that indicates if stored value is considered
 * 
 * @return The difference of the operands specified
*/
double calc_service_sub(struct calc_service_t* svc, double a, double b,
    bool_t mem) 
{
  double result = a - b;
  if (!mem) 
  {
    return result;
  }
  svc->mem = result - svc->mem;
  return svc->mem;
}

/**
 * Multiplication function with two options: Multiplication between two factors or
 * additionally consider the value stored.
 * 
 * @param svc Pointer to service object in use
 * @param a Operand 1
 * @param b Operand 2
 * @param mem Boolean that indicates if stored value is considered
 * 
 * @return Product of the operands specified
*/
double calc_service_mul(struct calc_service_t* svc, double a, double b,
    bool_t mem) 
{
  double result = a * b;
  if (!mem) 
  {
    return result;
  }
  svc->mem = result * svc->mem;
  return svc->mem;
}

/**
 * Division function that prevents the case of zero division
 * 
 * @param svc Pointer to service object in use
 * @param a Dividend
 * @param b Divisor
 * @param result Pointer that will be used to update result
 * 
 * @return Status ok or status zero division error, respective the case.
*/
int calc_service_div(struct calc_service_t* svc, double a, double b, double* result) 
{
  if (b == 0.0) 
  {
    return CALC_SVC_ERROR_DIV_BY_ZERO;
  }
  *result = a / b;
  return CALC_SVC_OK;
}
