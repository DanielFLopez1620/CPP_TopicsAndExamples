#ifndef COMMON_SERVER_CORE_H
#define COMMON_SERVER_CORE_H

#include <sys/socket.h>

struct client_addr_t;
struct client_context_t;

// Create custom type that refers to a generic pointer to a function that receives two
// parameters (the client ccontext and the response object).
typedef void (*write_resp_func_t)(struct client_context_t*, struct calc_proto_resp_t*);


// Attributes for client context

struct client_context_t 
{
  struct client_addr_t* addr;   // Adress
  struct calc_proto_ser_t* ser; // Serialization oobject
  struct calc_service_t* svc;   // Service object
  write_resp_func_t write_resp; // Function that will update response
};

typedef void (*write_resp_func_t)(struct client_context_t*, struct calc_proto_resp_t*);

// Callback implemented

void error_callback(void* obj, int ref_id, int error_code);
void request_callback(void* obj, struct calc_proto_req_t req);

// extern implies that the definition is implied to be somewhere else and the linker will solve it
// In this case, the socket adress definition is used for the stream/datagram communication
extern struct sockaddr* sockaddr_new();
extern socklen_t sockaddr_sizeof();

#endif
