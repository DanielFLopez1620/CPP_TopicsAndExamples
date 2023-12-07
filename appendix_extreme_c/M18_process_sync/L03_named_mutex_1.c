// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc, it may get stuck with the shared closing operations

#include <stdio.h>

/**
 * Mutexes in processes does not work like in the case of threads, and the reason is that you
 * will need a place accessible to all of them, and if you guessed correctly, we will need a 
 * shared memory region.
 * 
 * Test the code below with: 
 * 
 *      gcc L03_named_mutex_1.c -lrt -lpthread -o nm1.out
 *      ./ns.out
 * 
 * NOTE: We will use pthread.h as we need  the mutex functions for this.
*/

#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>


#define MEM_SIZE 4

// Shared file descriptor to get a shared memory object
int shared_fd = -1;

// Mutex shared file descriptor
int mutex_sh = -1;

// Pointer to the shared resource (in this case a counter)
int32_t* con = NULL;

// Pointer ot mutex implemented
pthread_mutex_t* mt = NULL;

// FUNCTION PROTOTYPES
void init_mutex();
void kill_mutex();
void init_shared_resource();
void shutdown_shared_resource();
void counter_process();

// MAIN
int main(int argc, char **argv)
{
    // Initialize shared resource 
    init_shared_resource();

    // Initialize semaphore
    init_mutex();

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
        kill_mutex();
    }

    printf("If you want to know more about this topic, check the next link:\n");
    printf("\nhttps://stackoverflow.com/questions/368322/differences-between-system-v-and-posix-semaphores.");
    return 0;
}

// FUNCTION DEFINITIONS

/**
 * Initialize control mechanism (mutex), and create the shared memory open
 * 
 * @exception Launches error message and exits if shared memory isn't created.
 * @exception Launches error message and exits if truncation of shared memory isn't achieved.
 * @exception Launches error message and exits if mapping the region wasn't possible.
 * @exception Launches error message and exits if the setting of attributes for mutex isn't possible.
 * @exception Launches error message and exits if the initialization of attributes for mutex isn't achieved.
 * @exception Launches error message and exits if the initialization of the mutex goes wrong.
 * @exception Launches error message and exits if the destruction of the mutex attributes fails.
*/
void init_mutex()
{
    mutex_sh = shm_open("/mutex0", O_CREAT | O_RDWR, 0600);
    if(mutex_sh < 0)
    {
        fprintf(stderr, "ERROR: Shared memory wasn't created: %s\n", strerror(errno));
        exit(1);
    }

    if (ftruncate(mutex_sh, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Truncation of mutex wasn't completed: %s\n", strerror(errno));
        exit(1);
    }

    void* map = mmap(0, sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE, MAP_SHARED, mutex_sh, 0);

    if(map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping wasn't possible: %s\n", strerror(errno));
        exit(1);
    }

    mt = (pthread_mutex_t*)map;

    int ini = -1;
    pthread_mutexattr_t attr;

    if((ini = pthread_mutexattr_init(&attr)))
    {
        fprintf(stderr, "ERROR: Problem with init attributes: %s\n", strerror(errno));
        exit(1);
    }

    if((ini = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)))
    {
        fprintf(stderr, "ERROR: Problem with setting the attributs: %s\n", strerror(errno));
        exit(1);
    }

    if((ini = pthread_mutex_init(mt, &attr)))
    {
        fprintf(stderr, "ERROR: Initializing mutex wasn't possible: %s\n", strerror(errno));
        exit(1);
    }

    if((ini = pthread_mutexattr_destroy(&attr)))
    {
        fprintf(stderr, "ERROR: Destroying attribute wasn't achieved: %s\n", strerror(errno));
        exit(1);
    }
}

/**
 * Shutdown control mechanism (mutex) and close shared memory.
 * 
 * @exception Launches an error and exits if the mutex cannot be destroyed.
 * @exception Launches an error and exits if the unmapping failed.
 * @exception Launches an error and exits if closing the shared file descriptor fails.
 * @exception Launches an error and exits if unlinking the shared memory isn't possible.
*/
void kill_mutex()
{
    int kll = -1;

    if((kll = pthread_mutex_destroy(mt)))
    {
        fprintf(stderr, "ERROR: Couldn't destroy mutex: %s\n", strerror(errno));
        exit(1);
    }

    if(munmap(mt, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping mutex not achieved: %s\n", strerror(errno));
        exit(1);
    }

    if(close(mutex_sh) < 0)
    {
        fprintf(stderr, "ERROR: Closing operation not achieved: %s\n", strerror(errno));
        exit(1);
    }

    if(shm_unlink("/mutex0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking region wasn't possible: %s\n", strerror(errno));
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
 * Simple counter with delays and mutex control mechanism implementaition.
*/
void counter_process()
{
    usleep(1);
    pthread_mutex_lock(mt);
    int32_t temp = *con;
    usleep(1);
    temp++;
    usleep(1);
}