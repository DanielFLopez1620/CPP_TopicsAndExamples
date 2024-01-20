#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include <sys/socket.h>

#include "common_client_core.h"

/**
 * The client will only have one serializer, as it is the oppositive of the server where every
 * client has its one separated serializer object.
 * 
 * Also, threads would be needed to read and avoid the blocking process with a sperate flow of
 * execution, the thread will read client's command line by recieving inputs provided by the user
 * using the terminal.
 * 
 * WHEN READY: Go to the code /server/unix/datagram/main.c
*/

/**
 * Reader of the buffer to check if it is valid to be serialized
 * 
 * @param obj Generic pointer to context obj
 * 
 * @return NULL if completed
 * 
 * @exception Launches an error and exits if the reading was not possible
*/
void* stream_response_reader(void* obj)
{
  struct context_t* context = (struct context_t*)obj;
  char buf[64];
  while (1) 
  {
    int ret = read(context->sd, buf, sizeof(buf));
    if (ret < 0) 
    {
      fprintf(stderr, "Read error! %s\n", strerror(errno));
      break;
    }
    if (ret == 0) 
    {
      break;
    }
    struct buffer_t b; b.data = buf, b.len = ret;
    calc_proto_ser_client_deserialize(context->ser, b, NULL);
  }
  return NULL;
}

/**
 * Stream client that reads messages, serializes and write it to send the request.
 * 
 * @param conn_sd Socket file descriptor for connections
*/
void stream_client_loop(int conn_sd) 
{
  // Generate context (for socket file descriptor)
  struct context_t context;
  context.sd = conn_sd;

  // Generate new serialization object
  context.ser = calc_proto_ser_new();
  calc_proto_ser_ctor(context.ser, &context, 128);
  calc_proto_ser_set_resp_callback(context.ser, on_response);
  calc_proto_ser_set_error_callback(context.ser, on_error);

  // Instance thread for reading the content on the file descriptor
  pthread_t reader_thread;
  pthread_create(&reader_thread, NULL,
          stream_response_reader, &context);

  char buf[128];
  printf("? (type quit to exit) ");
  while (1) 
  {
    // Read input provided
    scanf("%s", buf);
    int brk = 0, cnt = 0;
    struct calc_proto_req_t req;

    // Analize buffer and check it is valid
    parse_client_input(buf, &req, &brk, &cnt);
    if (brk)
    {
      break;
    }
    if (cnt) 
    {
      continue;
    }

    // Serialize request and write into the socket file descriptor
    struct buffer_t ser_req =
        calc_proto_ser_client_serialize(context.ser, &req);
    int ret = write(context.sd, ser_req.data, ser_req.len);
    
    // Check if the writting process was succesfully achieved
    if (ret == -1) 
    {
      fprintf(stderr, "Error while writing! %s\n",
              strerror(errno));
      break;
    }
    if (ret < ser_req.len) 
    {
      fprintf(stderr, "Wrote less than anticipated!\n");
      break;
    }
    printf("The req(%d) is sent.\n", req.id);
  }
  // Close the connection socket descriptor
  shutdown(conn_sd, SHUT_RD);

  // Destroy, close and free objects used
  calc_proto_ser_dtor(context.ser);
  calc_proto_ser_delete(context.ser);
  pthread_join(reader_thread, NULL);
  printf("Bye.\n");
}
