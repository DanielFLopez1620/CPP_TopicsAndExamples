#ifndef CALC_PROTO_SER_H
#define CALC_PROTO_SER_H

/**
 * Keep in mind that on the client side the request is serialized and the response is deserialized,
 * while in the server side it is the oppositive situation. So, you need to implemnt the 
 * serialization/deserialization process, but you will need more functions so they are accessible to
 * the respective parts. This includes three callbacks:
 * 
 * - One for recieving a request that has been deserialized.
 * - Other for receiving aresponse that has been deserialized.
 * - Another for receiving errors when the process fails.s
 * 
 * Go to the source code of teh implementations, and read the comments of the function to follow the
 * idea of the protocol.
 * 
 * WHEN READY: You can also check the test code and more on the request, but if you want to continue
 * go to the /calcsv directory and start with the 'calc_service.c", keep in mind that the test aren't
 * explained as they aren't the focues of this module.
*/

#include <types.h>

#include "calc_proto_req.h"
#include "calc_proto_resp.h"

#define ERROR_INVALID_REQUEST          101
#define ERROR_INVALID_REQUEST_ID       102
#define ERROR_INVALID_REQUEST_METHOD   103
#define ERROR_INVALID_REQUEST_OPERAND1 104
#define ERROR_INVALID_REQUEST_OPERAND2 105

#define ERROR_INVALID_RESPONSE         201
#define ERROR_INVALID_RESPONSE_REQ_ID  202
#define ERROR_INVALID_RESPONSE_STATUS  203
#define ERROR_INVALID_RESPONSE_RESULT  204

#define ERROR_UNKNOWN  220

// Struct that corresponds to the serialization of a message, saved as a text buffer.
struct buffer_t {
  char* data;
  int len;
};

struct calc_proto_ser_t;

// Definition of attributes for request/response objects with the corresponding serialization obj.
typedef void (*req_cb_t)(
        void* owner_obj,
        struct calc_proto_req_t);

typedef void (*resp_cb_t)(
        void* owner_obj,
        struct calc_proto_resp_t);

// Error callback type that relates for raising exception and prevention of bugs.
typedef void (*error_cb_t)(
        void* owner_obj,
        const int req_id,
        const int error_code);

// Memory mangament functions
struct calc_proto_ser_t* calc_proto_ser_new();
void calc_proto_ser_delete(
        struct calc_proto_ser_t* ser);

// Constructor and destructor
void calc_proto_ser_ctor(
        struct calc_proto_ser_t* ser,
        void* owner_obj,
        int ring_buffer_size);
void calc_proto_ser_dtor(
        struct calc_proto_ser_t* ser);


// Methods related with the serialization
void* calc_proto_ser_get_context(
        struct calc_proto_ser_t* ser);
void calc_proto_ser_set_req_callback(
        struct calc_proto_ser_t* ser,
        req_cb_t cb);
void calc_proto_ser_set_resp_callback(
        struct calc_proto_ser_t* ser,
        resp_cb_t cb);
void calc_proto_ser_set_error_callback(
        struct calc_proto_ser_t* ser,
        error_cb_t cb);
void calc_proto_ser_server_deserialize(
        struct calc_proto_ser_t* ser,
        struct buffer_t buffer,
        bool_t* req_found);
// Response serialization function
struct buffer_t calc_proto_ser_server_serialize(
        struct calc_proto_ser_t* ser,
        const struct calc_proto_resp_t* resp);
void calc_proto_ser_client_deserialize(
        struct calc_proto_ser_t* ser,
        struct buffer_t buffer,
        bool_t* resp_found);
struct buffer_t calc_proto_ser_client_serialize(
        struct calc_proto_ser_t* ser,
        const struct calc_proto_req_t* req);

#endif
