#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <datagram_server_core.h>

/**
 * UDP sockets are network sockets (and datagram sockets), so the socket type
 * would be SOCK_DGRAM, while the domain is still the same as the TCP.
 * 
 * As the datagram are still in use, the UDS is still valid here, and it is
 * the reason to keep the same implementation of serve forever on the UDS.
 * 
 * WHEN READY: Go to the client/udp/main.c file.
*/

/**
 * Manual allocator of socket adress objects
 * 
 * @return THe region where the object was allocated
*/
struct sockaddr* sockaddr_new() 
{
  return malloc(sizeof(struct sockaddr_in));
}

/**
 * Getter of the size of the socket adress structure
 * 
 * @return Size of structure
*/
socklen_t sockaddr_sizeof()
{
  return sizeof(struct sockaddr_in);
}

int main(int argc, char** argv) 
{

  // ----------- 1. Create socket object -----------------------------------
  // Domain is still AF_INET, but the type is nwo for datagrams
  int server_sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sd == -1) 
  {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file ----------------------------------

  // Prepare the address (and configure it properly for the socket)
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(9999);

  // Make binding of endpoint and check
  int result = bind(server_sd,(struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) 
  {
    close(server_sd);
    fprintf(stderr, "Could not bind the address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Start serving requests ---------
  serve_forever(server_sd);

  return 0;
}
