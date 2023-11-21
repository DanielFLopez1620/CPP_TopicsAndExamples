// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * The shared memory object exists as long as it is being used by at least one process (event
 *  when it is unlinked). But, how other process can access to a shared object...
 * I
 * In the code below, we create the case for that situation.
*/

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define MAX_SIZE 16

int main(int argc, char const *argv[])
{
    // Open the shared memory object with read only permission
    int shm_fd = shm_open("/shm0", O_RDONLY, 0600);
    if(shm_fd < 0)
    {
        fprintf(stderr, "ERROR: Failed to open shared memory: %s\n", strerror(errno));
        return 1;
    }

    fprintf(stdout, "Shared memory was opened succesfully...\n");

    // Map the memory content in read mode, to access to the content with the pointer
    void* map = mmap(0, MAX_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping of the region wasn't completed: %s\n", strerror(errno));
        return 1;
    }

    // Obtain the value or data stored in the shared memory by using the pointer and display it.
    char *content_ptr = (char*)map;
    fprintf(stdout, "Reading content in the shared memory:\n %s\n", content_ptr);
    
    // Unmap the memory region as it won't be used anymore in the program
    if(munmap(content_ptr, MAX_SIZE) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping wasn't completed: %s\n", strerror(errno));
        return 1;
    }

    // Close shared memory region
    if(close(shm_fd) < 0)
    {
        fprintf(stderr, "ERROR: Closing the shared memory failed: %s\n", strerror(errno));
        return 1;
    }

    // Unlink shared memory that was accessed
    if(shm_unlink("/shm0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking /shm0 failed: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
