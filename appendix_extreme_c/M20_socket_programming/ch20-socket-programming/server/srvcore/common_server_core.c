#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>

#include <calc_proto_ser.h>
#include <calc_service.h>

#include "common_server_core.h"

/**
 * Error callback function that will update status and handle the errors in the response object.
 * Result will be zero and status will relate with the error.
 * 
 * @param obj Generic poionter used to refer client context
 * @param ref_id ID of the request/response
 * @param error_code Error macro or number recieved
*/
void error_callback(void* obj, int ref_id, int error_code)
{
  struct client_context_t* context = (struct client_context_t*)obj;
  int status = STATUS_INTERNAL_ERROR;
  switch (error_code) 
  {
    case ERROR_INVALID_REQUEST:
      status = STATUS_INVALID_REQUEST; break;
    case ERROR_INVALID_REQUEST_ID:
      status = STATUS_INVALID_REQUEST; break;
    case ERROR_INVALID_REQUEST_METHOD:
      status = STATUS_INVALID_METHOD; break;
    case ERROR_INVALID_REQUEST_OPERAND1:
      status = STATUS_INVALID_OPERAND; break;
    case ERROR_INVALID_REQUEST_OPERAND2:
      status = STATUS_INVALID_OPERAND; break;
    case ERROR_UNKNOWN:
    default:
      break;
  }

  // Generate responses that notifies the situation
  struct calc_proto_resp_t resp;
  resp.req_id = ref_id;
  resp.status = status;
  resp.result = 0.0;
  context->write_resp(context, &resp);
}

/**
 * Callback for manage request received
 * 
 * @param obj Generic pointer that referst to the client conext related with the request
 * @param req Request object passed 
*/
void request_callback(void* obj, struct calc_proto_req_t req) 
{
  struct client_context_t* context = (struct client_context_t*)obj;
  int status = STATUS_OK;
  double result = 0.0;

  // Analize case and make the proper operation to formulate the response
  switch (req.method) 
  {
    case GETMEM:
      result = calc_service_get_mem(context->svc);
      break;
    case RESMEM:
      calc_service_reset_mem(context->svc);
      break;
    case ADD:
    case ADDM:
      result = calc_service_add(context->svc, req.operand1,
          req.operand2, req.method == ADDM);
      break;
    case SUB:
    case SUBM:
      result = calc_service_sub(context->svc, req.operand1,
          req.operand2, req.method == SUBM);
      break;
    case MUL:
    case MULM:
      result = calc_service_mul(context->svc, req.operand1,
          req.operand2, req.method == MULM);
      break;
    case DIV: 
    {
      status = calc_service_div(context->svc, req.operand1,
          req.operand2, &result);
      if (status == CALC_SVC_ERROR_DIV_BY_ZERO) 
      {
        status = STATUS_DIV_BY_ZERO;
      }
      break;
    }
    default:
      status = STATUS_INVALID_METHOD;
  }

  // Instance response object and pass the response by updating the context
  struct calc_proto_resp_t resp;
  resp.req_id = req.id;
  resp.status = status;
  resp.result = result;
  context->write_resp(context, &resp);
}
