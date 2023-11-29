// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc. 

#include <stdio.h>

/**
 * They are a useful tool to solve concurrency issues. They allow a better control over shared resources
 * which is ilustrated in the code below.
 * 
 * You can try this code:
 * 
 *      gcc L02_named_semaphores.c -lrt -lpthread -o ns.out
 *      ./ns.out
 * 
 * NOTE: The pthread library is needed because of the usage of semaphores. The -rt refers to the linking
 * process. Finally, remember that Windows is not POSIX-compliant in terms of semaphores.
*/

// Imports needed
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Function Prototypes

void init_sem();
void kill_sem();
void init_shared_resource();
void shutdown_shared_resource();
void counter_process();

// Shared resource definition object
#define MEM_SIZE 4
int shared_fd = -1;

// Pointer to shared resource
int32_t* con = NULL;

// Global pointer to the semaphore of the shared resource
sem_t* sem = NULL;

int main(int argc, char **argv)
{
    // Initialize shared resource 
    init_shared_resource();

    // Initialize semaphore
    init_sem();

    // Allocated and truncated shared memory
    if(ftruncate(shared_fd, MEM_SIZE * sizeof(char)) < 0)
    {
        fprintf(stderr, "ERROR: Failed to truncate region: %s\n", strerror(errno));
        return 1;
    }
    fprintf(stdout, "Memory region was truncated with success.\n");

    // Map memory and set write mode
    void* map = mmap(0, MEM_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);
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
    if(munmap(con, MEM_SIZE) < 0)
    {
        fprintf(stderr, "ERROR: Cannot unmap region: %s\n", strerror(errno));
        return 1;
    }

    // Closing the shared memory is also needed for both process.
    if(close(shared_fd) < 0)
    {
        fprintf(stderr, "ERROR: Failed to close shared memory: %s\n", strerror(errno));
        return 1;
    }

    // Only the parent needs to unlink the shared resource, and the same applies to the semaphore. 
    if(pid)
    {
        shutdown_shared_resource();
        kill_sem();
    }

    printf("If you want to know more about this topic, check the next link:\n");
    printf("\nhttps://stackoverflow.com/questions/368322/differences-between-system-v-and-posix-semaphores.");
    return 0;
}

// Function definitions

/**
 * Initialize semaphore for using a shared resource.
 * 
 * @exception If SEM_FAILED, launches an error message and stops the program.
*/
void init_sem()
{
    sem = sem_open("/sem0", O_CREAT | O_EXCL, 0600, 1);
    if(sem == SEM_FAILED)
    {
        fprintf(stderr, "ERROR: Initialization of semaphore wasn't completed: %s\n", strerror(errno));
        exit(1);
    }
}

/**
 * Shutdown the semaphore (close) and unlink the region created
 * 
 * @exception If it does not closes correctly, launches an error message and stop execution.
 * @exception If the unlink operation fails, launches an error message and stop execution.
*/
void kill_sem()
{
    if(sem_close(sem) < 0)
    {
        fprintf(stderr, "ERROR: Closing operation of semaphore wasn't completed: %s\n", strerror(errno));
        exit(1);
    }

    if(sem_unlink("/sem0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking shared memory wasn't possible: %s\n", strerror(errno));
        exit(1);
    }
}

/**
 * Open shared resources under the name /shm0 in read/write mode, and verify if it is
 * succesfully created.
 * 
 * @exception If shared resource opening isn't possible, display error message and stop execution
*/
void init_shared_resource()
{
    shared_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if(shared_fd < 0)
    {
        fprintf(stderr, "ERROR: Cannot create shared memory: %s\n", strerror(errno));
        exit(1);
    }
    fprintf(stdout, "Shared memory created: %d\n",shared_fd);
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
    // The reason fo rusing usleep calls is that we need to force the scheduler to
    // take back the CPU core. So, this allows us to see the effect of interleavings.
    usleep(1);
    sem_wait(sem);
    int32_t temporal = *con;
    usleep(1);
    temporal++;
    usleep(1);
    *con = temporal;
    sem_post(sem);
    usleep(1);
}