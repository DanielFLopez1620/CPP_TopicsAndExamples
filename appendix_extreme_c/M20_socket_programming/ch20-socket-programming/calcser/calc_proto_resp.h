#ifndef CALC_PROTO_RESP_H
#define CALC_PROTO_RESP_H


/**
 * When a request is done, you need to implement a form to response and generate a unique, valid
 * way to achieve that response.
 * 
 * For the calculator project, the response has the attributes/properties of request id, status and
 * result.
 * 
 * The status here is needed to identify if the processes has been finished or if there something
 * else you need to do.
 * 
 * So the response declaration should be:
 * 
 *    #include "calc_prot_resp.h"
 *    ...
 *        struct calc_proto_resp_resp resp;
 *        resp.req_id = 1620;
 *        resp.status = STATUS_OK;
 *        resp.result = 320;
 *    ...
 * 
 * And the respect serialization (that uses # as field delimitator and $ as message delimitator" 
 * should be:
 * 
 *    <req_id>#<status_num>#<result>$ --> 1620#0#320$
 * 
 * WHEN READY: Go to the code 'calc_proto_ser.c/.h', as we will move to the serialization process.
 * 
*/
#include <stdint.h>

#define STATUS_OK              0  // Everything seems to be good.
#define STATUS_INVALID_REQUEST 1  // Request ID wasn't identified
#define STATUS_INVALID_METHOD  2  // Mistype or unkown method
#define STATUS_INVALID_OPERAND 3  // Mistype or unkown operand
#define STATUS_DIV_BY_ZERO     4  // Common implementation to preven Cero Division Exception
#define STATUS_INTERNAL_ERROR  20 // Other will appear here.

typedef int status_t;

// Struct for defining the response.
struct calc_proto_resp_t {
  int32_t req_id;
  status_t status;
  double result;
};

#endif
