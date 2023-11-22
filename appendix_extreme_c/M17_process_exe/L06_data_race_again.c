// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * As you have seen, data race is a problem and you should take care in your code when
 * using threads.
*/

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Define size for shared resource space
#define SHARED_SIZE 4

int shared_fd = -1;

int32_t* con = -1;

// Function prototypes
void init_shared_resource();
void shutdown_shared_resource();
void counter_process();

// Main
int main(int argc, char **argv)
{
    // Initialize shared resource 
    init_shared_resource();

    // Allocated and truncated shared memory
    if(ftruncate(shared_fd, SHARED_SIZE * sizeof(char)) < 0)
    {
        fprintf(stderr, "ERROR: Failed to truncate region: %s\n", strerror(errno));
        return 1;
    }
    fprintf(stdout, "Memory region was truncated with success.\n");

    // Map memory and set write mode
    void* map = mmap(0, SHARED_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);
    if (map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping the region failed: %s\n", strerror(errno));
        return 1;
    }

    // Get the begin of the shared memory and initialize the counter
    con = (int32_t*)map;
    *con = 0;

    // Create a new process and check if it created succesfully (a child appear)
    pid_t pid = fork();
    if (pid)
    {
        // Parent process is still in charge
        counter_process();
        fprintf(stdout, "Parent is in charge of the counter: %d\n", *con);
        int status = -1;
        wait(&status); 
        fprintf(stdout, "Child process has ended with status: %d\n", status);
    }
    else
    {
        // Child process was created and is in charge now.
        counter_process();
        fprintf(stdout, "Child is in charge of the counter: %d\n", *con);
    }

    // Unmap memory region (it is needed for both parent and child)
    if(munmap(con, SHARED_SIZE) < 0)
    {
        fprintf(stderr, "ERROR: Cannot unmap region: %s\n", strerror(errno));
        return 1;
    }

    // Closing the shared memory is also needed for both process.
    if(close(shared_fd) < 0)
    {
        fprintf(stderr, "ERROR: Failed to close shared memory: %s\n");
        return 1;
    }

    // Only the parent needs to unlink the shared resource 
    if(pid)
    {
        shutdown_shared_resource();
    }

    return 0;
}

// Function definitions

/**
 * Open shared resources under the name /shm0 in read/write mode, and verify if it is
 * succesfully created.
*/
void init_shared_resource()
{
    shared_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if(shared_fd < 0)
    {
        fprintf(stderr, "ERROR: Cannot create shared memory: %s\n", strerror(errno));
        exit(1);
    }
}

/**
 * Close (unlink) the shared resource called /shm0 and verify if it was completed.
*/
void shutdown_shared_resource()
{
    if (shm_unlink("/shm0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking was not completed: %s\n", strerror(errno));
    }
}

/**
 * A function that acts as a counter with micro delays.
*/
void counter_process()
{
    usleep(1);
    int32_t temporal = *con;
    usleep(1);
    temporal++;
    *con = temporal;
    usleep(1);
}