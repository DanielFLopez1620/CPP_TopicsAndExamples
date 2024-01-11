#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "calc_proto_ser.h"

#define FIELD_COUNT_PER_REQ_MESSAGE 4
#define FIELD_COUNT_PER_RESP_MESSAGE 3
#define MESSAGE_DELIMITER '$' // Used for separation of different message
#define FIELD_DELIMITER '#' // Used for separation of attributes inside a message

// Structure that defines attributes for serialization/deserialization process
struct calc_proto_ser_t {
  char* ring_buf;
  int buf_len;         // Lenght of message
  int curr_idx;        // Current index of buffer
  int start_idx;       // Start index of the buffer
  error_cb_t error_cb; // Error callback
  req_cb_t req_cb;     // Request callback
  resp_cb_t resp_cb;   // Response callback
  void* context;       // Pointer to function for contextual operation
};

typedef void (*parse_and_notify_func_t)(struct calc_proto_ser_t* ser);


/**
 * Private function to parse a int to a string or char array
 * 
 * @param str Char array or string to store the number converted
 * @param Pointer to int variable to convert.
 * 
 * @return TRUE if the convertion is achieved
*/
bool_t _parse_int(const char* str,  int* num) 
{
  // sscanf reads formatted input from a string, and returns 1 if the reading was achieved
  // %d as if it was in a print, indicates an integer.
  if (sscanf(str, "%d", num) == 1) 
  {
    return TRUE;
  }
  return FALSE;
}


/**
 * Private function to parse a double to a string or char array
 * 
 * @param str Char array or string to store number converted
 * @param num Pointer to double variable to convert.
 * 
 * @return TRUE if the convertion is achieved
*/
bool_t _parse_double(const char* str, double* num) 
{
  // sscanf reads formatted input from a string, and returns 1 if the reading was achieved
  // %lf comes from long float which is equivalent to double in this case
  if (sscanf(str, "%lf", num) == 1) 
  {
    return TRUE;
  }
  return FALSE;
}

/**
 * Private function to serialize a double number for message sending
 * 
 * @param str Destination string/char array to store serialized number
 * @param num Double value to serialize
*/
void _serialize_double(char* str, double num) 
{
  char tmp[64];

  // sprintf sends formatted value to string or char array,
  // in this case $lf refers to long float values (doubles).
  sprintf(tmp, "%lf", num);

  // Make a copy to the returned value by pointer
  strcpy(str, tmp);

  // Add termitation character to the string (\0)
  int i = strlen(str) - 1;
  while (str[i] == '0' && i >= 0) i--;
  if (i >= 0) str[i + 1] = '\0';
  if (i >= 0 && str[i] == '.') str[i] = '\0';
}

/**
 * Private function for checking if buffer still has space left.
 * 
 * @param ser Pointer to serialization object in use
 * 
 * @return FALSE if the buffer isn't full, TRUE otherwise
*/
bool_t _is_buffer_full(struct calc_proto_ser_t* ser) 
{
  if (ser->start_idx < 0) 
  {
    return FALSE;
  }

  // If the assert result in true, it does nothing. Otherwise, sends an error by using stderr
  assert(ser->start_idx != ser->curr_idx);

  // Validates that the current index is further that the start index, then calculates the lenght of both
  // and finally, it is compared to the buffer lenght to determinate if it is full
  if (ser->start_idx < ser->curr_idx) 
  {
    return (ser->curr_idx - ser->start_idx) == (ser->buf_len - 1);
  }
  return (ser->start_idx - ser->curr_idx) == 1;
}

/**
 * 
*/
bool_t _parse_fields(struct calc_proto_ser_t* ser, char** fields,
    int field_count, int error_code) 
{
  int end_idx = ser->curr_idx;
  int idx = ser->start_idx;
  char *ptr = ser->ring_buf + ser->start_idx;
  int field_idx = 0;
  while (field_idx < field_count) 
  {
    fields[field_idx] = ptr;
    while (*ptr != FIELD_DELIMITER) 
    {
        if (idx == end_idx) 
        {
          break;
        }
        if (idx == (ser->buf_len - 1)) 
        {
          idx = 0;
        }
        ptr++; idx++;
    }
    
    if (field_idx < (field_count - 1)) 
    {
      if (*ptr != FIELD_DELIMITER) 
      {
        if (ser->error_cb) ser->error_cb(ser->context, -1, error_code);
        return FALSE;
      }
      *ptr = '\0'; ptr++; idx++;
    } else 
    {
      if (*ptr != MESSAGE_DELIMITER) 
      {
        if (ser->error_cb) ser->error_cb(ser->context, -1, error_code);
        return FALSE;
      }
      *ptr = '\0';
      assert(idx == end_idx);
      if (idx != end_idx) 
      {
        if (ser->error_cb) ser->error_cb(ser->context, -1, error_code);
        return FALSE;
      }
    }
    field_idx++;
  }

  // Checks if all the index has been passed.
  assert(field_idx == field_count);
  return TRUE;
}

void _parse_req_and_notify(struct calc_proto_ser_t* ser) {
  char* fields[FIELD_COUNT_PER_REQ_MESSAGE];
  if (!_parse_fields(ser, fields, FIELD_COUNT_PER_REQ_MESSAGE, ERROR_INVALID_REQUEST)) {
    return;
  }
  struct calc_proto_req_t req;
  if (!_parse_int(fields[0], &req.id)) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, -1, ERROR_INVALID_REQUEST_ID);
      return;
    }
  }
  req.method = str_to_method(fields[1]);
  if (req.method == NONE) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, req.id, ERROR_INVALID_REQUEST_METHOD);
      return;
    }
  }
  if (!_parse_double(fields[2], &req.operand1)) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, req.id, ERROR_INVALID_REQUEST_OPERAND1);
      return;
    }
  }
  if (!_parse_double(fields[3], &req.operand2)) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, req.id, ERROR_INVALID_REQUEST_OPERAND2);
      return;
    }
  }
  if (!ser->req_cb) {
    fprintf(stderr, "Request callback is not set!\n");
    return;
  }
  ser->req_cb(ser->context, req);
}

void _parse_resp_and_notify(struct calc_proto_ser_t* ser) {
  char* fields[FIELD_COUNT_PER_RESP_MESSAGE];
  if (!_parse_fields(ser, fields, FIELD_COUNT_PER_RESP_MESSAGE, ERROR_INVALID_RESPONSE)) {
    return;
  }
  struct calc_proto_resp_t resp;
  if (!_parse_int(fields[0], &resp.req_id)) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, 0, ERROR_INVALID_RESPONSE_REQ_ID);
      return;
    }
  }
  if (!_parse_int(fields[1], &resp.status)) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, resp.req_id, ERROR_INVALID_RESPONSE_STATUS);
      return;
    }
  }
  if (resp.status > 4) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, resp.req_id, ERROR_INVALID_RESPONSE_STATUS);
      return;
    }
  }
  if (!_parse_double(fields[2], &resp.result)) {
    if (ser->error_cb) {
      ser->error_cb(ser->context, resp.req_id, ERROR_INVALID_RESPONSE_RESULT);
      return;
    }
  }
  if (!ser->resp_cb) {
    fprintf(stderr, "Response callback is not set!\n");
    return;
  }
  ser->resp_cb(ser->context, resp);
}

/**
 * Private deserialization function
 * 
 * @param ser Pointer to serialization object in use
 * @param buff Buffer that contains the serialized message.
 * @param func Pointer to the function paser_and_notify_func_t
 * @param error_code Feed a error code to consider
 * @param found Boolean flag to check the request.
*/
void _deserialize(struct calc_proto_ser_t* ser, struct buffer_t buff,
    parse_and_notify_func_t func, int error_code, bool_t* found) 
{
  if (buff.len > ser->buf_len) {
      if (ser->error_cb) {
        ser->error_cb(ser->context, -1, error_code);
      }
      return;
  }
  bool_t overflow = FALSE;
  int i = 0;
  for (; i < buff.len; i++) {
    ser->ring_buf[ser->curr_idx] = buff.data[i];
    if (_is_buffer_full(ser)) {
      if (ser->error_cb) {
        ser->error_cb(ser->context, -1, error_code);
      }
      overflow = TRUE;
      ser->curr_idx = 0;
      ser->start_idx = -1;
      break;
    }
    if (ser->ring_buf[ser->curr_idx] == MESSAGE_DELIMITER &&
        ser->start_idx >= 0) {
      if (found) {
        *found = TRUE;
      }
      func(ser);
      ser->start_idx = -1;
    } else if (ser->ring_buf[ser->curr_idx] != MESSAGE_DELIMITER &&
               ser->start_idx < 0) {
      ser->start_idx = ser->curr_idx;
    }
    ser->curr_idx++;
    if (ser->curr_idx == ser->buf_len) {
      ser->curr_idx = 0;
    }
  }
  if (overflow) {
    _deserialize(ser, buff, func, error_code, found);
  }
}

struct calc_proto_ser_t* calc_proto_ser_new() {
  return (struct calc_proto_ser_t*)malloc(sizeof(struct calc_proto_ser_t));
}

void calc_proto_ser_delete(struct calc_proto_ser_t* ser) {
  free(ser);
}

void calc_proto_ser_ctor(struct calc_proto_ser_t* ser, void* context, int ring_buffer_size) {
  ser->buf_len = ring_buffer_size;
  ser->ring_buf = (char*)malloc(ser->buf_len * sizeof(char));

  ser->curr_idx = 0;
  ser->start_idx = -1;

  ser->req_cb = NULL;
  ser->resp_cb = NULL;
  ser->error_cb = NULL;

  ser->context = context;
}

void calc_proto_ser_dtor(struct calc_proto_ser_t* ser) {
  free(ser->ring_buf);
}

void* calc_proto_ser_get_context(struct calc_proto_ser_t* ser) {
  return ser->context;
}

void calc_proto_ser_set_req_callback(struct calc_proto_ser_t* ser, req_cb_t req_cb) {
  ser->req_cb = req_cb;
}

void calc_proto_ser_set_resp_callback(struct calc_proto_ser_t* ser, resp_cb_t resp_cb) {
  ser->resp_cb = resp_cb;
}

void calc_proto_ser_set_error_callback(struct calc_proto_ser_t* ser, error_cb_t error_cb) {
  ser->error_cb = error_cb;
}
/**
 * Function for response deserialization
 * 
 * @param ser Pointer to the serialization object in use
 * @param buff Buffer that contains the serialized message of interest.
 * @param req_found Boolean flag to check for valid request
 * 
*/
void calc_proto_ser_server_deserialize(
    struct calc_proto_ser_t* ser,
    struct buffer_t buff,
    bool_t* req_found) 
{
  if (req_found) 
  {
    *req_found = FALSE;
  }

  // Deserialization process by
  _deserialize(ser, buff, _parse_req_and_notify,
          ERROR_INVALID_REQUEST, req_found);
}

/**
 * Function for response serialization
 * 
 * @param ser Pointer to serialization object in use.
 * @param resp Pointer to a response objectec that needs to be serialized.
 * 
 * @return Serialized message that implements the message and field delimitator.
*/
struct buffer_t calc_proto_ser_server_serialize(
    struct calc_proto_ser_t* ser,
    const struct calc_proto_resp_t* resp) 
{
    // Create buffer
    struct buffer_t buff;
    char resp_result_str[64];
    
    // Get response and reserve memory (use private function for double serialization)
    _serialize_double(resp_result_str, resp->result);
    buff.data = (char*)malloc(64 * sizeof(char));

    // Sends string (formatted) by using a pointer (like a print that goes to a str)
    sprintf(buff.data, "%d%c%d%c%s%c", resp->req_id,
            FIELD_DELIMITER, (int)resp->status, FIELD_DELIMITER,
      resp_result_str, MESSAGE_DELIMITER);

    // Update length
    buff.len = strlen(buff.data);
    return buff;
}


void calc_proto_ser_client_deserialize(
    struct calc_proto_ser_t* ser,
    struct buffer_t buff, bool_t* resp_found) 
{
  if (resp_found) {
    *resp_found = FALSE;
  }
  _deserialize(ser, buff, _parse_resp_and_notify,
          ERROR_INVALID_RESPONSE, resp_found);
}

struct buffer_t calc_proto_ser_client_serialize(
    struct calc_proto_ser_t* ser,
    const struct calc_proto_req_t* req) {
  struct buffer_t buff;
  char req_op1_str[64];
  char req_op2_str[64];
  _serialize_double(req_op1_str, req->operand1);
  _serialize_double(req_op2_str, req->operand2);
  buff.data = (char*)malloc(64 * sizeof(char));
  sprintf(buff.data, "%d%c%s%c%s%c%s%c", req->id, FIELD_DELIMITER,
          method_to_str(req->method), FIELD_DELIMITER,
          req_op1_str, FIELD_DELIMITER, req_op2_str,
          MESSAGE_DELIMITER);
  buff.len = strlen(buff.data);
  return buff;
}
