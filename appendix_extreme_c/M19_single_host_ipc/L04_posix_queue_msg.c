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
 * Check the code below, and see how message queues works in a basic example.
 * 
 *      gcc L04_posix_queue_msg.c -lrt -o mq.out
 *      ./mq.out
 * 
 * NOTE: Message queues aren't available on macOS.
 * 
 * You may notice that without a consumer, the content can be acumulated and then block the process,
 * and this is the main limitation of pipes and messages queues. One alternative can be the socktes.
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h> // Header needed for using message queues

#define BUFFER_SIZE 32 // Size of buffer for reading

int main(int argc, char** argv)
{
    printf("\tExample of using POSIX message queues:\n");

    mqd_t msg_queue;

    // Structu for defining attributes of messages
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = BUFFER_SIZE;
    attr.mq_curmsgs = 0;

    // Fork process to use communication between parent and child
    int child = fork();
    if(child == -1)
    {
        fprintf(stderr, "ERROR: Couldn't fork process!\n");
        exit(1);
    }

    // The child will be the sender
    if(child == 0)
    {
        // Delay of one second, wait time for parent to be ready
        sleep(1);

        // Open message queue shared resource in write only mode
        mqd_t msg_queue = mq_open("/mq0", O_WRONLY);

        // Write msg, log and wait
        char msg[] = "Hello World from Child!";
        fprintf(stdout, "CHILD will wait 2 seconds...\n");
        sleep(2);
        fprintf(stdout, "CHILD is writting to father...\n");

        // Send message and close channel for child
        mq_send(msg_queue, msg, strlen(msg) + 1, 0);
        mq_close(msg_queue);
    }

    // Paren will be the reciever
    else
    {
        // Open shared memory in read only mode (and creates it if it doesn't exists)
        mqd_t msg_queue = mq_open("/mq0", O_RDONLY | O_CREAT, 0644, &attr);
        
        // Create buffer and log ready
        char buffer[BUFFER_SIZE];
        fprintf(stdout, "FAHTER is reading from CHILD...\n");

        // Read message and display it
        int size_msg = mq_receive(msg_queue, buffer, BUFFER_SIZE, NULL);
        fprintf(stdout, "Father received a message: %s\n", buffer);
        
        // Close and unlink shared memory region for message queue
        mq_close(msg_queue);
        mq_unlink("/mq0");
    }

    printf("If you want to know more, explore the next links:\n");
    printf("- https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/mq_overview.html. \n");
    return 0;
}
