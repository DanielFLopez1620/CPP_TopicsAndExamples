// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * As a review, there are two types of IPC techniques: pull-based (which require a accesible medium)
 * and push based (which require a channel), so the main difference is related with the way of
 * retrieving data. Our main focus will be push-based techniques with blocking approach, mostly with
 * sockets that allows a two way channel/communication. By using sockets we can use 'connection-
 * oriented' (data streams) or 'connection-less' (datagram) approaches, also we have to keep in mind
 * the protocols (TCP for streams and UDS for datagrams).
 * 
 * This module is heavily based on the 'Calculator Project' of the book, so you are going to see a fork
 * (with the corresponding credit and license of the author), with some additional comments made by
 * author of the current repository.
 * 
 * STRUCTURE: The repo of example contains the following (more details will be added on the comments of
 * the codes).
 * 
 * - /calcser: Which comes from "Calculator Serializer", it is the serializer/deserializer library which 
 *   was build into a static library (libcalcser.a)
 * 
 * - /calsvs: Which comes from "Calculator Service" , which is different from the server process as this 
 *   contains the core functionalties of the calculatores (build in libcalcsvc.a).
 * 
 * - /server/srvcore: It contains the sources common for the server processes (streams or datagrams), 
 *   and all the code is in the static library file named 'libsrvcore.a'.
 * 
 * - /server/unix/stream: For using stream channels behind a UDS, and comes with an executable to bring 
 *   the calculator service (unix_stream_calc_server).
 * 
 * - /server/unix/datagram: For using datagram channels behind a UDS, the executable related is 'unix_
 *   datagram_calc_server"
 * 
 * - /server/tcp: TCP network sockets for using stream channels (tcp_calc_server).
 * 
 * - /server/udp: UDP network sockets of using datagram channels (udp_calc_server).
 * 
 * - /client/clicore: Which comes from 'Client Core' and it is core for stream and datagram client
 *   processes, so it doesn't matter if they are using UDS or network sockets. It is present in the 
 *   'libclicore.a' library.
 * 
 * - /client/unix/stream: Specific client that uses stream channels with UDS (unix_stream_calc_client 
 *   is the executable).
 * 
 * - /client/unix/datagram: Specific client that uses datagram channels with UDS (the executable is
 *   unix_datagram_calc_client).
 * 
 * - /client/tcp: Client program that uses stream channels with TCP Sockets (tcp_calc_client).
 * 
 * - /client/udp: Client program that uses datagram channels with UDP socket (udp_calc_client).
 *  
 * Finally, for building the project, you will need cmake, you will learn of this tool in the future,
 * for now, just execute the next commands:
 * 
 *      cd ch20-socket-programming
 *      mkdir -p build
 *      cmake ..
 *      make
 * 
 * And for executing it, you can run (in the case of client with UDS):
 * 
 *      cd ch20-socket-programming
 *      ./client/unix/strem/unix_stream_calc_client
 * 
 * NOTE: The most important part is the complete application protocol, so it allows you the communication
 * between the two parts.
 * 
*/

int main(int argc, char **argv)
{
    printf("This module will use the 'Calculator Project' of the original book:\n");
    printf("\tExtrem C Repo: https://github.com/PacktPublishing/Extreme-C\n");
    printf("You can clone the code or extract the folder you need!\n");
    printf("Do not forget to check the additional comments of explanation\n");
    return 0;
}
