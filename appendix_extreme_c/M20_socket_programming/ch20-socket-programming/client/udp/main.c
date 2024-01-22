#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>

#include <datagram_client_core.h>

/**
 * UDP client is pretty similar to the TCP client, but with the changes of the
 * socket type, and the idea with the 'datagram_client_loop' is to generate the
 * connection with the incoming datagrams.
 * 
 * WHEN READY: You are ready to move on Module 21, do not forget to check other
 * commented codes on this section and try your own modifications to understand
 * better the functionality of the project.
*/

int main(int argc, char** argv) 
{

  // ----------- 1. Create socket object -------------------------------------
  // By using INET configuration during datagrams
  int conn_sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (conn_sd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ------------ 2. Connect to server-- --------------------------------------
  // Find the IP address behind the hostname
  char host[] = "localhost";
  struct hostent* host_entry;
  host_entry = gethostbyname(host);
  if (!host_entry) 
  {
    fprintf(stderr, "Could not resolve the host '%s'\n", host);
    exit(1);
  }

  // Prepare the address and make it consistent for the socket
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr = *((struct in_addr*)host_entry->h_addr);;
  addr.sin_port = htons(9999);

  // Make the connection using the address and check
  int result = connect(conn_sd, (struct sockaddr*)&addr,
          sizeof(addr));
  if (result == -1) {
    close(conn_sd);
    fprintf(stderr, "Could no connect: %s\n", strerror(errno));
    exit(1);
  }

  // Client connection for datagrams
  datagram_client_loop(conn_sd);

  return 0;
}
