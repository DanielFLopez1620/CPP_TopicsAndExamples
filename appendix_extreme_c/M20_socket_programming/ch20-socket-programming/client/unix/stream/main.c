#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <stream_client_core.h>

/**
 * Once the server stream was implemented, we need to follow the connector sequence (UDS), but 
 * for the connection you will need to specify a UDS endpoint.
 * 
 * The most notorious change from the server is the change of 'bind' to 'connect'.
 * 
 * WHEN READY: GO to the file: 'client/clicore/stream_client_core.c'
*/

int main(int argc, char** argv)
{
  // Socket file descriptor, must be the same of the server
  char sock_file[] = "/tmp/calc_svc.sock";

  // ----------- 1. Create socket object ----------------------------------------------------------
 
  // The socket type must be congruent with the specified in the server
  int conn_sd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (conn_sd == -1) 
  {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Connect to server ---------------------

  // Prepare the address
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sock_file, sizeof(addr.sun_path) - 1);

  // Make connection (instaed of bind) and check if it is valid
  int result = connect(conn_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) 
  {
    close(conn_sd);
    fprintf(stderr, "Could no connect: %s\n", strerror(errno));
    exit(1);
  }

  stream_client_loop(conn_sd);

  return 0;
}
