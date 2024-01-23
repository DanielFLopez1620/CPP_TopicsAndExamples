#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include "common_client_core.h"

/**
 * Convert string/char array to double
 * 
 * @param str Pointer to the string/char array to read
 * @param num Pointer to num to save the value
 * 
 * @return 1 if the conversion is valid, 0 otherwise.
*/
int _to_double(const char* str, double* num) 
{
  return sscanf(str, "%lf", num) == 1 ? 1 : 0;
}

/**
 * Private function that convert an error received and passes it to string, to future displays
 * for warnings or exceptions.
 * 
 * @param error_code Constant, macro or number related with the error received in other process.
 * 
 * @return Char pointer to array with the traslation of the error.
*/
const char* _error_to_str(int error_code) 
{
  switch (error_code) 
  {
    case ERROR_INVALID_RESPONSE: 
      return "INVALID_RESPONSE";
    case ERROR_INVALID_RESPONSE_REQ_ID: 
      return "INVALID_REQUEST_ID";
    case ERROR_INVALID_RESPONSE_STATUS: 
      return "INVALID_STATUS";
    case ERROR_INVALID_RESPONSE_RESULT: 
      return "INVALID_RESPONSE";
    default: 
      return "(UNKOWN)";
  }
}

/**
 * Private function that convert a status received and passes it to string, to use it in messages
 * or logging functions.
 * 
 * @param status Status request received to convert to string
 * 
 * @return Char pointer to conversion of the status to string
*/
const char* _status_to_str(status_t status) 
{
  switch (status) 
  {
    case STATUS_OK: 
      return "OK";
    case STATUS_INVALID_REQUEST: 
      return "INVALID_REQUEST";
    case STATUS_INVALID_METHOD: 
      return "INVALID_METHOD";
    case STATUS_INVALID_OPERAND: 
      return "INVALID_OPERAND";
    case STATUS_DIV_BY_ZERO: 
    return "DIV_BY_ZERO";
    case STATUS_INTERNAL_ERROR: 
      return "INTERNAL_ERROR";
    default: 
      return "(UNKNOWN)";
  }
}

/**
 * Function that acts in case of error to log the error, as it refers to ID error or others.
 * 
 * @param obj General pointer to object that generate error (can be serialization object)
 * @param req_id ID for request
 * @param error_code Error code raised
*/
void on_error(void* obj, int req_id, int error_code) 
{
  if (req_id > 0) 
  {
    fprintf(stderr, "Serializer error on req(%d): %s\n", req_id, _error_to_str(error_code));
  } 
  else 
  {
    fprintf(stderr, "Serializer error: %s\n", _error_to_str(error_code));
  }
  printf("? (type quit to exit) "); fflush(stdout);
}

/**
 * Function that log and report status/response for a response properly managed.
 * 
 * @param obj Pointer to generic object related with the process of serialization, req or res.
 * @param resp Struct that contains the response managed 
*/
void on_response(void* obj, struct calc_proto_resp_t resp) 
{
  printf("req(%d) > status: %s, result: %lf\n", resp.req_id, _status_to_str(resp.status),
          resp.result);
  printf("? (type quit to exit) "); fflush(stdout);
}

/**
 * Function that handles the input provided by the user and make a proper request.
 * 
 * @param buf Buffer where the response was loaded
 * @param req Pointer to request object that will store the data needed to create a proper request
 * @param brk Break flag
 * @param cnt Continue flag
 * 
 * @exception If the operand NONE is received, will log error and exit function
 * @exception If reset and get memory are passed with operands, will log error and exit function
*/
void parse_client_input(char* buf, struct calc_proto_req_t* req, int *brk, int *cnt) 
{
  // Initialization of request attributes
  static int req_id = 0;
  double op1 = 0.0, op2 = 0.0;
  method_t method = NONE;

  // Creation of pointers to convert/update values
  char* sign, *op1_str, *op2_str;

  // Conditionals to check and update operand
  if (!strcmp(buf, "quit")) 
  {
    *brk = 1;
    return;
  } 
  else if (!strcmp(buf, "mem")) 
  {
    method = GETMEM;
  } 
  else if (!strcmp(buf, "reset")) 
  {
    method = RESMEM;
  }
  else if ((sign = strstr(buf, "++")) > 0) 
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 2;
    method = ADDM;
  } 
  else if ((sign = strstr(buf, "+")) > 0) 
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 1;
    method = ADD;
  } 
  else if ((sign = strstr(buf, "--")) > 0) 
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 2;
    method = SUBM;
  } 
  else if ((sign = strstr(buf, "-")) > 0) 
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 1;
    method = SUB;
  } 
  else if ((sign = strstr(buf, "**")) > 0) 
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 2;
    method = MULM;
  } 
  else if ((sign = strstr(buf, "*")) > 0) 
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 1;
    method = MUL;
  } 
  else if ((sign = strstr(buf, "/")) > 0)
  {
    *sign = '\0';
    op1_str = buf;
    op2_str = sign + 1;
    method = DIV;
  } 
  else 
  {
    fprintf(stderr, "Invalid input!\n");
    printf("? (type quit to exit) "); fflush(stdout);
    *cnt = 1;
    return;
  }
  if (method == NONE) 
  {
    fprintf(stderr, "No method could be deduced!\n");
    printf("? (type quit to exit) "); 
    fflush(stdout);
    *cnt = 1;
    return;
  }
  if (method != GETMEM && method != RESMEM) 
  {
    if (!_to_double(op1_str, &op1) || !_to_double(op2_str, &op2)) 
    {
      fprintf(stderr, "Invalid operands!\n");
      printf("? (type quit to exit) "); 
      fflush(stdout);
      *cnt = 1;
      return;
    }
  }
  req->id = req_id++;
  req->method = method;
  req->operand1 = op1;
  req->operand2 = op2;
}
