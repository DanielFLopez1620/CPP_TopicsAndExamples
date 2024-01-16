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
#include "stream_server_core.h"

/**
 * The last thing we talk about was the 'accept_forever' function that was blocking, go and check 
 * it for more info. One important aspect to know is that it is valid for other stream sockets
 * and can be re-used.
 * 
 * NOTE: Another option for implement a forever client, is use 'event loops' instaed of 'infite
 * loops with multithreading'.
 * 
 * WHEN READY: Go to the stream client, in the file: client/unix/stream/main.c
*/

// Client adress attributes only related with the socket descriptor 
struct client_addr_t 
{
  int sd;
};

/**
 * Write and upate response in the socket file descriptor
 * 
 * @param context Pointer to the client conext to use
 * @param resp Pointer to response calculated
*/
void stream_write_resp(
        struct client_context_t* context,
        struct calc_proto_resp_t* resp) 
{
  // Serialize response and check if it works
  struct buffer_t buf = 
      calc_proto_ser_server_serialize(context->ser, resp);
  if (buf.len == 0) 
  {
    close(context->addr->sd);
    fprintf(stderr, "Internal error while serializing response\n");
    exit(1);
  }

  // Write serialized message from the buffer to the socket descriptor and check bytes
  int ret = write(context->addr->sd, buf.data, buf.len);
  free(buf.data);
  if (ret == -1) 
  {
    fprintf(stderr, "Could not write to client: %s\n",
            strerror(errno));
    close(context->addr->sd);
    exit(1);
  } 
  else if (ret < buf.len) 
  {
    fprintf(stderr, "WARN: Less bytes were written!\n");
    exit(1);
  }
}

/**
 * Function that manages the incoming client's request
 * 
 * @param arg Pointer to the arguments of the request
 * 
 * @return NULL if everything goes right
*/
void* client_handler(void *arg) 
{
  // Create client context, update value and free argument after setting up
  struct client_context_t context;
  context.addr = (struct client_addr_t*)
      malloc(sizeof(struct client_addr_t));
  context.addr->sd = *((int*)arg);
  free((int*)arg);

  // Instance new serialization object
  context.ser = calc_proto_ser_new();
  calc_proto_ser_ctor(context.ser, &context, 256);
  calc_proto_ser_set_req_callback(context.ser, request_callback);
  calc_proto_ser_set_error_callback(context.ser, error_callback);

  // Instance new calculation service object
  context.svc = calc_service_new();
  calc_service_ctor(context.svc);

  context.write_resp = &stream_write_resp;

  int ret;
  char buffer[128];
  while (1) 
  {
    // Read info in adress specified
    // Note that the same API can be used for file or sockets descriptors.
    int ret = read(context.addr->sd, buffer, 128);
    if (ret == 0 || ret == -1) 
    {
      break;
    }

    // Update buffer and make deserialization
    // The process would make possible to call the deserialization many times before completing a
    // full deserialized request
    struct buffer_t buf;
    buf.data = buffer; buf.len = ret;
    calc_proto_ser_server_deserialize(context.ser, buf, NULL);
  }

  // Delete and free object used
  calc_service_dtor(context.svc);
  calc_service_delete(context.svc);

  calc_proto_ser_dtor(context.ser);
  calc_proto_ser_delete(context.ser);

  free(context.addr);

  return NULL;
}
/**
 * Manage and accept infinite incoming client connections
 * (Blocking function, and here is the importance multithreading)
 * 
 * @param server_sd Socket related with server
*/
void accept_forever(int server_sd) 
{
  // Infinite loop
  while (1) 
  {
    // Accept incoming connection and validate
    int client_sd = accept(server_sd, NULL, NULL);
    if (client_sd == -1) 
    {
      close(server_sd);
      fprintf(stderr, "Could not accept the client: %s\n",
              strerror(errno));
      exit(1);
    }

    // Create thread with arg that contains the socket file, then use client handler
    pthread_t client_handler_thread;
    int* arg = (int *)malloc(sizeof(int));
    *arg = client_sd;
    int result = pthread_create(&client_handler_thread, NULL,
            &client_handler, arg);
    if (result) 
    {
      // Do not forget to close the connections in case of error
      close(client_sd);
      close(server_sd);
      free(arg);
      fprintf(stderr, "Could not start the client handler thread.\n");
      exit(1);
    }
  }
}
