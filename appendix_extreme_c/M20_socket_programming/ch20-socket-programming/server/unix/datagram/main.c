#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <datagram_server_core.h>

/**
 * We have already talked about streams, but for communication we also need to cover datagrams, as
 * they have their own listener and connector sequence for transmission, the server should
 * implement UDS and it will be our focus here. 
 * 
 * Datagram channels are connection-less, therefore, it is not 1-to-1 so the request and the
 * response must it in one single datagram to allow the message handling. Which results in the size
 * being very important and the size is related with the underlying channel as UDP sockets rely on
 * the network configuration.
 * 
 * One change to keep in mind are the I/O API as we are no longer using 'read' and 'write', but
 * instead we use 'recvfrom' (receive from) and 'sendto', which allow to keep the track
 * of it.
 * 
 * NOTE: If you want to learn about correct size on datagrams, you can read:
 * https://stackoverflow.com/questions/21856517/whats-the-practical-limit-on-the-size-of-single-
 * packet-transmitted-over-domain
 * 
 * WHEN READY: Go to the file /server/srvcore/datagram-server_core.c
*/

/**
 * Manually allocate a new socket adress object
 * 
 * @return Direction of the allocated memory
*/
struct sockaddr* sockaddr_new() 
{
  return malloc(sizeof(struct sockaddr_un));
}

/**
 * Obtain the lenght/size of the socket adress object
 * 
 * @return Base size of object
*/
socklen_t sockaddr_sizeof() 
{
  return sizeof(struct sockaddr_un);
}


int main(int argc, char** argv) 
{
  // Name for socket file descriptor
  char sock_file[] = "/tmp/calc_svc.sock";

  // ----------- 1. Create socket object ----------------------------------------------------------
  // For this case, we will use SOCK_DGRAM (Socket Datagram) instead of  SOCK_STREAM
  int server_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (server_sd == -1) 
  {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file -----------------------------------------------------------  
  // Delete the previously created socket file if it exists.
  unlink(sock_file);

  // Prepare the address (type/domain must be compatible with the socket)
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sock_file, sizeof(addr.sun_path) - 1);

  // Bind endpoint and check 
  int result = bind(server_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) 
  {
    close(server_sd);
    fprintf(stderr, "Could not bind the address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Start serving requests --------------------------------------------------------
  serve_forever(server_sd);

  return 0;
}
