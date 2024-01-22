#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <stream_server_core.h>

/**
 * There is another family of sockets used, the AF_INET which have a protocol
 * needed to use them (TCP and UDP).
 * 
 * First, let's talk about a TCP server, they specifies a differet adress family
 * AF_INET, and have a different socket adresses requirement. But for the rest
 * is almost the same implementation.
 * 
 * WHEN READY: Go to the code /client/tcp/main.c
*/

/**
 * Manual allocator for socket adress objects
 * 
 * @return Space where the object is allocated
*/
struct sockaddr* sockaddr_new() 
{
  return malloc(sizeof(struct sockaddr_in));
}

/**
 * Getter of the size of socket address
 * 
 * @return Size of structure
*/
socklen_t sockaddr_sizeof() 
{
  return sizeof(struct sockaddr_in);
}

int main(int argc, char** argv) 
{

  // ----------- 1. Create socket object --------------------------------------
  // Focus your attetion in the change of AF_UNIX to AF_INET
  int server_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sd == -1) 
  {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file --------------------------------------

  // Prepare the address (that is build different than UDS)
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY; // Internet address
  addr.sin_port = htons(6666);       // Port number 

  // Binding process
  int result = bind(server_sd, (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) 
  {
    close(server_sd);
    fprintf(stderr, "Could not bind the address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Prepare backlog -------------------------------------------
  // Configuring backlog for server with 10 connections request in wait
  result = listen(server_sd, 10);
  if (result == -1) 
  {
    close(server_sd);
    fprintf(stderr, "Could not set the backlog: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 4. Start accepting clients -----------------------------------
  accept_forever(server_sd);

  return 0;
}
