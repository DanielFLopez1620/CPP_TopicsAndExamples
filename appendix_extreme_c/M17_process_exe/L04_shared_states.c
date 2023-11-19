// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * They are needed as one process cannot have all the resources, and they would be needed somewhere
 * else. For making this possible, you need to put it in a 'place' is available for other, or you
 * sent the state to share it. So we can generate a classification in two types, 'pull-based' techniques
 * (require a medium of storage) and the 'push-based' (related to a channel or transmission).
 * 
 * For now, we will cover the ones related with pull-based, we can mention the next ones:
 * 
 * - SHARED MEMORY: A region that is shared (and available) to some process, which is a space in
 *   memory. And remember, it is temporary.
 * - FILESYSTEM: Save and use, it is the oldest one, but it can lead to difficulties in the 
 *  synchronization for the access.
 * - NETWORK SERVICES: Once it is connected,, it can be used to store and retrieve shared states.
 * 
 * For now, let's check an example of the POSIX standard to share memory, keep in mind that for process
 * it is impossible to access to the memory of other process, so shared mechanism are needed. The
 * example code create and populate a shared memory object according to the standards.
 * 
 * Here a shared memory object is created (/shm0) with 16 bytes and fill it with a name of four characters
 * (including the enter space). The shared memory will be there until rebooting the system or unlinking it
 * by using a process. You can found the region in the /dev/shm directory.
 * 
 * You can execute the code with:
 *      gcc L04_shared_states.c -lrt -o shm.out
 *      ./shm.out
 *      ls /dev/shm
 *      cat /dev/shm/shm0
 * 
 * NOTE: The -lrt is mandatory because a link to the rt library is needed.
*/

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define MAX_SIZE 16

int main(int argc, char **argv)
{
    // shm, comes from SHared Memory
    // First, we create a shared memory object called /shm0, then we specify the creation and that
    // the region can be using for writing and reading. Finally, it has a permission sequence that 
    // tells that it is available for reading and wrtiting by the process owned by the creator of the shm.
    int shm_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if(shm_fd < 0)
    {
        fprintf(stderr, "ERRROR: Cannot create shared memory: %s\n", strerror(errno));
        return 1;
    }
    fprintf(stdout, "Shared memory creation was completed withouth problems: %d\n", shm_fd);

    // Truncate the shared memory, it would be needed in companion of the max size.
    if( ftruncate(shm_fd, MAX_SIZE * sizeof(char)) < 0)
    {
        fprintf(stderr, "ERROR: FAiled to truncate: %s\n", strerror(errno));
        return 1;
    }
    fprintf(stdout, "Memory region was truncated with success...\n");

    // Creation of a map to access to the shared memory, it is indicated that it can be used for
    // writing and it is shared for process.
    void* map = mmap(0, MAX_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Memory mapping failed: %s\n", strerror(errno));
        return 1;
    }

    // Using the map created to populate the memory region.
    char* word_ptr = (char*)map;
    word_ptr[0] = 'D';
    word_ptr[1] = 'a';
    word_ptr[2] = 'n';
    word_ptr[3] = '\n';
    word_ptr[4] = '\0';

    while(1);

    fprintf(stdout, "Data has been loaded in the shared memory.\n");

    // Similar to pointers there are final steps that shouldn't be missing, like unmappin the 
    // region
    if(munmap(word_ptr, MAX_SIZE) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping wasn't possible: %s\n", strerror(errno));
        return 1;
    }

    // Finally, closing the shared memory
    if (close(shm_fd) < 0)
    {
        fprintf(stderr, "ERROR: Cannot close shared memory: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
