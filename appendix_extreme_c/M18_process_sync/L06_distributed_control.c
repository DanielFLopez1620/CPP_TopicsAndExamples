// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * The concurrency exposed in the previous four modules was centered in a single machine (single-host 
 * software), but this is not always the case, sometimes you need a distributed network, but before
 * moving on, keep in mind the next info:
 * 
 * - As you have multiple machines, you are experiencing parallelism instaed of concurrency, because
 *   each machine has its own proessor. But this doesn't mean interleavings will dissapear.
 * 
 * - Not every process is going to be written in the same program, so the integration of them would
 *   need control mechanisms.
 * 
 * - The processes aren't always in the same machine, and you always communicate using a network, so 
 *   messsages would be needed.
 * 
 * - Using a network, means that latency (not receiving a message immediately) exits and you should 
 *   keep an eye on the security (prevent attacks and secure the info)
 * 
 * - You need other types of mechanism, such as message validation (Does the reciever really recieve
 *   the message).
 * 
 * To achieving distribuited systems (and keep them transactional and synchronized), you can use:
 * 
 * - CENTRALIZED PROCESS SYNCHORINIZATION: Uses a central process (or node) that manages the other
 *   processes (which must be in communication with the central node), the master node manages
 *   (approves) orders to enter critical sections.
*/