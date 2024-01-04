// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * SOCKET PROGRAMMING: It happens mostly in the transport layer (responsible for connection two 
 * processes over an Internet layer). The communication can be managed as 'process-to-process-
 * communication' and 'host-to-host-communication'. But before moving on, let's talk part by part.
 * 
 * - SOCKET: Something dedicated that identifies the connections, so for one connection between 
 *   two processes there is a socket on each side that adresses the connection. For using them,
 *   there is the 'socket library' and POXIS version of it.
 * 
 * - POSIX SOCKET LIBRARY: Every socket has a domain, type and protocol. In the case of the domain
 *   which is also known as 'address family (AF)' (which can be connection-oriented or connection-
 *   less), and they include AF_LOCAL (process on same host), AF_INET (with IPv4) or AF_INET6 (as
 *   you suppose, it uses IPv6). For the case of type attribute, some are SOCK_STREAM (connection-
 *   oriented with delivery, correcteness and order), SOCK_DGRAM (connection-less and datagrams,
 *   data chunks), SOCK_RAW (it allows the kernel to understand the connection and transport
 *   protocol and the package delivery is direct). 
 * 
 * Finally, for this moduel, let's review the stream sequence
 * 
 * - Listener sequence:
 *   1) Creation of socket object with 'socket' function (usually a listener),  and the args needed
 *      which are the attributes.
 *   2) Bound 'endpoint' (IP address and port in most cases).
 *   3) Configure the socket for listening with 'listen' function, and it creates a backlog, do not
 *      forget to consider a proper size.
 *   4) Acccept the incoming communication (yes, with the 'accept' function), note that each call 
 *      will pick up a single connection (usually the next one in the backlog). 
 * 
 * - Connector sequence:
 *   1) Create a socket using 'socket' function and must have a compatible domain.
 *   2) Then use the 'connect' function with the args needed for identify the listener endpoint.
 * 
 * The connectors should respect the type of comunication (or if it uses datagram or streams), also
 * keep in mind that for datagram you cannot have a dedicated session for incomming connections.
 * 
 * NOTE: The 'accept','connect' functions will alway return a new object socket, this means that 
 * the kernel always dedicates a new slocket every connection accepted.
 *  
 * NOTE: Sockets have their own descriptor inside the kernel, but they can be accessed and you can 
 * also use 'read' and 'write' functions.
 *  
*/

int main(int argc, char const *argv[])
{
    printf("Read the comment on the final thought on socket programming...\n");
    printf("In the next module we will implement them.\n");
    return 0;
}
