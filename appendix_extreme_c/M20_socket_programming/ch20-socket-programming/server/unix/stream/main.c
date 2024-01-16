#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h> // Contains function needed to create socket objects  (POSIX HEADER)
#include <sys/un.h> // Also related with sockets, but for the side of adresses

#include <stream_server_core.h>

/**
 * A server can be considered in the beginning as a listener (sequence). The step for this process are:
 * 
 * 1. Socket object creation.
 * 2. Binding socket file.
 * 3. Prepare backlock.
 * 4. Accept clients.
 * 
 * Look each item and learn how to create them.
 * 
 * NOTE: Keep in mind that the files for sockets cannot excceed 104 chars in Unix or 108 in Linux.
 * 
 * WHEN READY: Go to the code /server/srvcore/strem_server_core.c
*/

int main(int argc, char** argv) 
{
  // Name of socket file (absolute path)
  char sock_file[] = "/tmp/calc_svc.sock";

  // ----------- 1. Create socket object ------------------------------------------------------
  
  // Remember sockets has 3 attributes: family/domain, type and protocol.
  int server_sd = socket(AF_UNIX, SOCK_STREAM, 0);
  
  // Validate cretion of socket
  if (server_sd == -1) 
  {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 2. Bind the socket file ------------------------------------------------------

  // Delete the previously created socket file if it exists.
  unlink(sock_file);

  // Prepare the (named) address
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX; // Domain must be compatible with the socket obj.
  strncpy(addr.sun_path, sock_file, sizeof(addr.sun_path) - 1);

  // Binding process will succeed only if  there is no other socket file bound to the socket obj.
  int result = bind(server_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) 
  {
    close(server_sd);
    fprintf(stderr, "Could not bind the address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Prepare backlog --------------------------------------------------------------
  // Will configure the backlog according an already bound obj and set a limit of connections.
  result = listen(server_sd, 10);
  if (result == -1) 
  {
    close(server_sd);
    fprintf(stderr, "Could not set the backlog: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 4. Start accepting clients -------------------------------------------
  accept_forever(server_sd);
  //NOTE: accept_forever is a blocking function, so the main would never stop

  // If you need to accept clients one by one, you can follow the next implementation:
  // while(1)
  // {
  //   int client_sd = accept(server_sd, NULL, NULL);
  //   if(client_sd == -1)
  //   {
  //     close(server_sd);
  //     fprintf(stderr, "Couldn't accept incoming client: %s\n", strerror(errno));
  //     exit(1);
  //   }
  //   ...
  // }

  return 0;
}
