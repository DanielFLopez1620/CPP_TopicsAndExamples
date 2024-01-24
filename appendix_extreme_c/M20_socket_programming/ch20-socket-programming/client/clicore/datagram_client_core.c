#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include <sys/socket.h>

#include "common_client_core.h"

/**
 * Function that check , read, load and deserialize the socket file descriptor datagram for a
 * future request that will be made.
 * 
 * @param obj Generic pointer used to manage context object
 * 
 * @return NULL the process is achieved
*/
void* datagram_response_reader(void* obj) 
{
  // Use generic pointer to abstract the context
  struct context_t* context = (struct context_t*)obj;

  // Instance char array for buffer reading
  char buf[64];

  while (1) 
  {
    // Receive context (read socket file descriptor) and load it into the buffer
    // We could use `read` since we don't need the source address.
    int ret = recvfrom(context->sd, buf, sizeof(buf), 0, NULL, NULL);
    if (ret < 0) 
    {
      fprintf(stderr, "Read error! %s\n", strerror(errno));
      break;
    }
    if (ret == 0) 
    {
      break;
    }
    // Update buffer 
    struct buffer_t b; b.data = buf, b.len = ret;

    // Deserialize message and update context
    calc_proto_ser_client_deserialize(context->ser, b, NULL);
  }
  return NULL;
}

/**
 * Loop for client connection that will analize the datagram deserialized and process a prpoper
 * request.
 * 
 * @param conn_sd Connection socket file descriptor
*/
void datagram_client_loop(int conn_sd) 
{
  // Generate context for client request
  struct context_t context;
  context.sd = conn_sd;
  context.ser = calc_proto_ser_new();
  calc_proto_ser_ctor(context.ser, &context, 128);
  calc_proto_ser_set_resp_callback(context.ser, on_response);
  calc_proto_ser_set_error_callback(context.ser, on_error);

  // Create thread for reading the serialized buffer of the request and respond
  pthread_t reader_thread;
  pthread_create(&reader_thread, NULL, datagram_response_reader, &context);

  char buffer[128];
  printf("? (type quit to exit) ");

  // Client loop
  while (1) 
  {
    
    // Read input from terminal
    scanf("%s", buffer);
    int brk = 0, cnt = 0;
    struct calc_proto_req_t req;

    // Analize buffer to check for cotext of the request
    parse_client_input(buffer, &req, &brk, &cnt);

    // Cases for operation of exit or invalid character detected
    if (brk) 
    {
      break;
    }
    if (cnt) 
    {
      continue;
    }

    // Serialize request processed
    struct buffer_t buf = calc_proto_ser_client_serialize(context.ser, &req);
    
    // Write response into socket file descriptor 
    // We could use `write` since we already know the destination.
    int ret = write(context.sd, buf.data, buf.len);

    // Check for error during writting
    free(buf.data);
    if (ret == -1) 
    {
      fprintf(stderr, "Error while writing! %s\n", strerror(errno));
      break;
    }
    if (ret < buf.len) {
      fprintf(stderr, "Wrote less than anticipated!\n");
      break;
    }

    // Log that request was send
    printf("The req(%d) is sent.\n", req.id);
  }
  // Close connection made
  shutdown(conn_sd, SHUT_RD);

  // Join threade after being used
  pthread_join(reader_thread, NULL);

  // Destroy and delete object used
  calc_proto_ser_dtor(context.ser);
  calc_proto_ser_delete(context.ser);
  printf("Bye.\n");
}
