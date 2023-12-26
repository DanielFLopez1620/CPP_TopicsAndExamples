// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

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
 * be translated, the process for this is know as 'serailization' (and its oppositive 'deserialization)
 * 
 * 
*/