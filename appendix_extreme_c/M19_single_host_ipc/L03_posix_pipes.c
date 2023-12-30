// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Pipes are unidirectional channels that can be used to exchange info via messages, it needs two
 * file descriptors (one for sending and other for reading).
 * 
 * 
 * For achieving a communication with pipes, keep in mind that one of the processes should setup
 * the file descriptor and transfer it to other processes, or use a named pipe.
 * 
 * NOTE: AS the child process waits two seconds, it pauses the parent in the 'read' funcgtion.
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 40

int main(int argc, char const *argv[])
{
    printf("\tBasic usage of pipes:\n");

    // Creating pipe, by declaring first the array of two file descriptors
    // Position 0 is for reading, and position 1 is for writing.
    int file_descriptors[2];
    pipe(file_descriptors);

    int child = fork();
    if(child == -1)
    {
        fprintf(stderr, "Couldn't create child process!\n");
        exit(1);
    }

    // Child will be the sender
    if(child == 0)
    {
        // Close father's file descriptor
        close(file_descriptors[0]);

        // Preparing message sending
        char message[] = "Hello World from the Child";
        fprintf(stdout, "Child will wait 2 seconds...\n");
        sleep(2);
        fprintf(stdout, "Child sending message to father...\n");

        // Write message in buffer
        write(file_descriptors[1], message, strlen(message) + 1);
    }
    // Father will be the reciever
    else
    {
        // Closes child's file descriptor
        close(file_descriptors[1]);

        // Prepare buffer and read message 
        char buffer[BUFFER_SIZE];
        fprintf(stdout, "Fahter is ready to receive child's info\n");
        int message_len = read(file_descriptors[0], buffer, BUFFER_SIZE);
        fprintf(stdout, "Message received from child was: %s\n", buffer);
    }
    return 0;
}
