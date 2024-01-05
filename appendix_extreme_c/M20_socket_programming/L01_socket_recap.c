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
 * - /server/unix/stream: For using channels behind a UDS, and comes with an executable to bring the
 *   calculator service.
 *  
 * NOTE: The most important part is complete application protocol, so it allows you the communication
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
