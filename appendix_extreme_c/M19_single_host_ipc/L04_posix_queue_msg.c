// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * POSIX MESSAGE QUEUES: They follow a similar idea of pipes like the unidirectional communication, 
 * the limited capacity, usage of I/O functions and being connection-less/no ownership present,
 * but they differ in the following points:
 * 
 * - Pipes keep bytes, but message queues holds messages (they have structure).
 * - Pipes has a maximum size, instaed message queues doesn't have limit messages, but the messages
 *   have a limit of bytes.
 * - Message queues always open a file, which can be used for other processes.
 * - Message queues can be prioritized.
 * 
 * NOTE: Message queues aren't available on macOS.
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>

int main(int argc, char **argv)
{
    printf("\tExample of using POSIX message queues:\n");

    mqd_t msg_queue;

    struct msq_queue_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 32;
    attr.mq_curmsgs = 0;

    printf("If you want to know more, explore the next links:\n");
    printf("- https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/mq_overview.html. \n");
    return 0;
}
