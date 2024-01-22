#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>

#include <stream_client_core.h>

/**
 * The client is similar to the UDS stream client, and are limited to the main 
 * implementation.
 * 
 * As implemented in the TCP server, the sockets are now from the AF_INET
 * domain, and therefore are changes in the adress implementation that should 
 * be consistent with the previous definition from the client.
 * 
 * NOTE: Remember that TCP sockets are stream sockets, and it is the reason for 
 * implementing the same code on the handling process of new clients.
 * 
 * WHEN READY: Go to the code server/udp/main.c
*/

int main(int argc, char** argv) 
{

  // ----------- 1. Create socket object --------------------------------------
  // Now using AF_INET domain
  int conn_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (conn_sd == -1) 
  {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ------------ 2. Connect to server-- --------------------------------------

  // Find the IP address behind the hostname (on your machine)
  char host[] = "localhost";
  struct hostent* host_entry;
  host_entry = gethostbyname(host);
  if (!host_entry) 
  {
    fprintf(stderr, "Could not resolve the host '%s'\n", host);
    exit(1);
  }

  // Prepare the address (following the idea from the server)
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr = *((struct in_addr*)host_entry->h_addr);;
  addr.sin_port = htons(6666);

  // Make the connection, using the adress configured 
  int result = connect(conn_sd, (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) 
  {
    close(conn_sd);
    fprintf(stderr, "Could no connect: %s\n", strerror(errno));
    exit(1);
  }

  // Loop client
  stream_client_loop(conn_sd);

  return 0;
}
