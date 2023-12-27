// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * IPC: Which comes from Inter-Process Communicaction, it is used to mention the communication and 
 * transmission of data, the ones mentioned from the previous modules can also be considered IPC,
 * some techniques can be shared memory, using the filesystem, POSIX signal, POSIX pipes, POSIX
 * message queues, domain sockets or internet sockets.
 * 
 * The ones explored in the previous module (shared memory and filesystem) can be categorized as 
 * 'pull-based' IPC techniques, the other ones apply under the name 'push-based'.
 * 
 * Before moving, we need to define a 'message' which contains a series of bytes that follows a 
 * well-defined interface, protocol or standard, and if it is used for communication,
 * the processes using it should know the message structure.
 * 
 * Now, let's mention some differences between pull and push based techniques. 
 * 
 * - In 'pull-based' there is an external resource or medium available (files, internet) where they
 *   pull info, while in 'push-based' there are channels of communications (where messages are sent/
 *   delivered, but not stored).
 * 
 * - In 'pull-based' the access to the medium must be sunchrhonized, while in 'push-based' it is not
 *   needed.
 * 
 * - In 'pull-based' the processes can operate independently (due to storage of info), but in 'push-
 *   based' the process must run at the same time (due to loss of messages if one of them isn't
 *   available, note that there are buffers for incomming messages in the kernel).
 * 
 * COMMUNITACTION PROTOCOLS: When communicating, both processes should understand each other (as if
 * they speak in the same languages), so they need a 'protocol', but why? If they only uses bytes,
 * the answer is related with the message lenght and the message content, also they bytes needs to
 * be translated, the process for this is know as 'serialization' (and its oppositive 'deserialization)
 * 
 * Choosing a communication protocol always will need serialization in order to send messages, as here
 * the order is carefully followed, for example, HTTP (Yes, you know it, the Hyper Text Transfer Protocol)
 * with text content and DNS (Domain Name service) with binary protocol. And if you ask about programming
 * languages, the serialization libraries can be provided in different languages, therefore the development
 * doesn't need to be in the same language (HTTP has for C, C++, Python...).
 * 
 * PROTOCOL CHARACTERISTICS: Not every protocol follows the same rules, but there are some key points:
 * 
 * - Content type: It can be textual (alphanumerical), binary (usually 8 bytes, 256 bits) or a combination
 *  of both. Here also plays a role the compression (better with textual content). For example, JSON is
 *  textual and BSON is combinated.
 * 
 * - Lenght of message: It can be 'fixed-lenght' (all the messages from one type has the same) or 'variable-
 *   lenght'. When using fixed-length, you reduce the risk of losing info as you already know the waited bits
 *   size. And in the case for using 'variable-lenght', it is good to use structure to define and understand
 *   the message, some techniques used are 'delimiters' (a special character as division), 'framing' (carrying
 *   and indicator in the first bytes to indicate the length) and FSM (Finite State Machines, should be aware
 *   of the status and grammar).
 * 
 * - Sequentiality: The communication is like a store, for getting a response on a product you need to ask 
 *   (request-response), in other terms we have a client (sender) and a server (listener), and this process
 *   is asynchronous (the sender isnt' blocked when the reply is being processed).
 * 
 * Before starting to program single-host communication, keep in mind that the focus will be POSIX signals,
 * POSIX pipes, POSIX message queues and Unix domain sockets. Also, file descriptors are important to
 * understand, as the communication of two processes can be in the same machine, so they are used
 * to write (modify) and read data, they are usually found in the /dev directory and can be considered an IPC
 * channel.
*/

int main(int argc, char **argv)
{
    printf("Read the intro in the comments, and let's continue the journey with processes\n");
    return 0;
}
