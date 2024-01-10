#ifndef CALC_PROTO_REQ_H
#define CALC_PROTO_REQ_H

#include <stdint.h>

/**
 * The application protocol allows the communication, so it has to be well-defined, for the calculator
 * exists a variable-lenght protocol (so, it has an unique identifier).
 * 
 * The request message (defined below) has four attributes or fields that are the request ID, the 
 * method, and the two operands (first and second).
 * 
 * So, in case you need a definition, you need to implement a object of this class:
 * 
 *    #include "calc_prto_req.h"
 *    ...
 *        struct calc_proto_req_t req;
 *        req.id = 1620;
 *        req.method = MUL;
 *        req.operand1 = 16:
 *        req.operand2 = 20;
 *    ...
 * 
 * NOTE: A serialization would be needed, for the calculator project it should be:
 *      
 *    <ID>#<Method>#<operand1>#<operand2>$  ,for example, 1620#MUL#16#20$
 * 
 * WHEN READY: Continue with the code of /calcser/clac_proto_resp.h.
*/

// Custom enumeration for methods
typedef enum {
  NONE,   // Void method
  GETMEM, // Read value in memory
  RESMEM, // Restore value in memory
  ADD,    // Add two numbers
  ADDM,   // Add two numbers plus the value stored in memory
  SUB,    // Substract two numbers
  SUBM,   // Subsctract two numbers and also considers the value stored in memory
  MUL,    // Multiply two factors
  MULM,   // Multiply two factos, then the value stored in memory
  DIV     // Divide the first number into the second one
} method_t;

// Struct for request message
struct calc_proto_req_t {
  int32_t id;
  method_t method;
  double operand1;
  double operand2;
};

// Functions related to method identification or traslation
method_t str_to_method(const char*);
const char* method_to_str(method_t);

#endif
