#ifndef COMMON_CLIENT_CORE_H
#define COMMON_CLIENT_CORE_H

#include <calc_proto_ser.h>
#include <calc_proto_req.h>


/**
 * Context attributes
*/
struct context_t 
{
  int sd;                        // Socket file attribute
  struct calc_proto_ser_t* ser;  // Serialization object
};


// Methods and functions related with response and request management from the client
int _to_double(const char* str, double* num);

const char* _error_to_str(int error_code);
const char* _status_to_str(status_t status);

void on_error(void* obj, int req_id, int error_code);
void on_response(void* obj, struct calc_proto_resp_t resp);

void parse_client_input(char* buf, struct calc_proto_req_t* req, int *brk, int*cnt);

#endif
