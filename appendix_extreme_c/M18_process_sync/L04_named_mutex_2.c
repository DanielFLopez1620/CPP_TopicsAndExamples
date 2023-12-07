// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc, it may get stuck with the shared closing operations

#include <stdio.h>

/**
 * When using shared resources and mutex, you do not need to fork processes, also mutexes can be
 * used to end different processes. So, check and read the code below to see the usage of a mutex.
 * 
 * You can compile and run the code with the next command:
 * 
 *      gcc L04_named_mutex_2.c -lpthread -lrt -o nm2.out
 *      ./nm2.out
 * 
 * NOTE: When using 'pthread_mutex_lock' and 'pthread_mutex_unlock', it is recommended to check the
 * returned value.
*/

// Header files
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Definition of shared memory names
#define MT_SHM "/mutex0"
#define SHM "/shm0"

// Cancel flag implementations
int cancel_flag = -1; // Flag for checking cancelations (or interrupts)
int cancel_flag_owner = 0; // Check if the process is the owner of the shared memory object
int* cancel_flag_ptr = NULL;

// Mutex implementation description
int mt_shm_fd = -1; // Mutex shared memory file descriptor
int mt_owner = 0; // Check if the mutex is the owner of the shared memory object
pthread_mutex_t* mt = NULL;

// FUNCTION PROTOTYPES
void init_shr();
void shutdown_resource();
void init_mutex();
void shut_mutex();
int check_cancelation();
void cancel();
void signal_handler(int);

// MAIN
int main(int argc, char **argv)
{
    // Signal definition to handle Keyboard Interrupt (Ctrl + C)
    signal(SIGINT, signal_handler);

    // Initialize resources and control mechanism
    init_shr();
    init_mutex();

    // Log progress before cancelation
    while(!check_cancelation())
    {
        fprintf(stdout, "Still working...\n");
        sleep(1);
    }

    fprintf(stdout, "Cancel signal was received...\n");

    // Shutdown and close resources and control mechanism
    shutdown_resource();
    shut_mutex();

    return 0;
}

// FUNCTION DEFINITIONS


/**
 * Init shared resource (checks if it is available or if the creation is needed).
 * 
 * @exception Launches a warn if the shared memory object isn't available.
 * @exception Launches an error and exits if the shared memory object wasn't created.
 * @exception Launches an error and exits if the truncation fails.
 * @exception Launches an error and exits if the mapping wasn't achieved
*/
void init_shr()
{
    // Try to open shared resources (with only the flag for read/write)
    cancel_flag = shm_open(SHM, O_RDWR, 0600);
    // Check if the shared resource is available, in order to prevent an additional creation.
    if(cancel_flag >= 0)
    {
        cancel_flag_owner = 0;
        fprintf(stdout, "Shared memory object opened successfully.\n");
    }
    // If not detected, create the shared memory object
    else if(errno == ENOENT)
    {
        fprintf(stderr, "WARN: Memory object wasn't opened.\n");
        fprintf(stdout, "Trying again, now with the creation of memory object...\n");
        
        // Try to open the sahred resources, now with additional flags for creation
        cancel_flag = shm_open(SHM, O_CREAT | O_EXCL | O_RDWR, 0600);
        if(cancel_flag >= 0)
        {
            cancel_flag_owner = 1;
            fprintf(stdout, "Shared memory object was created successfully.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Failed to create memory object again: %s\n", strerror(errno));
            exit(1);
        }
    }
    // If it wasn't possible, sends error.
    else
    {
        fprintf(stderr, "ERROR: Memory object creation failed: %s\n", strerror(errno));
        exit(1);
    }

    // If resource is available, then it truncates the region and check if it was possible
    if(cancel_flag_owner)
    {
        if(ftruncate( cancel_flag, sizeof(__uint16_t)) < 0)
        {
            fprintf(stderr, "ERROR: Truncation wasn't possible: %s\n", strerror(errno));
            exit(1);
        }
        fprintf(stdout, "The memory region is now truncated...\n");
    }

    // Then, it maps the shared memory
    void* map = mmap(0, sizeof(__uint16_t), PROT_WRITE, MAP_SHARED, cancel_flag, 0);
    if(map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping wasn't achieved: %s\n", strerror(errno));
        exit(1);
    }

    // Finally validates the state and assign the pointer
    cancel_flag_ptr = (__uint16_t*)map;
    if(cancel_flag_owner)
    {
        *cancel_flag_ptr = 0;
    }
}

/**
 * Shutdown shared resources (including cases of ownership)
 * 
 * @exception Launches an error and exits if the unmapping fails.
 * @exception Launches an error and exits if the closing operation of the shared memory goes wrong.
 * @exception Launches an error and exits if the unlink operation isn't achieved.
*/
void shutdown_resource()
{
    // Unmap the shared memory by using the pointer of the mapped region
    if(munmap(cancel_flag_ptr, sizeof(__uint16_t)) < 0)
    {
        fprintf(stderr, "ERROR: Unmpaping wasn't achieved: %s\n", strerror(errno));
        exit(1);
    }

    // Close the shared region 
    if(close(cancel_flag) < 0)
    {
        fprintf(stderr, "ERROR: Shared resource couldn't be closed: %s\n", strerror(errno));
        exit(1);
    }

    // Unlink process in case that the shared resource was used
    if(cancel_flag_owner)
    {
        sleep(1);
        if(shm_unlink(SHM) < 0)
        {
            fprintf(stderr, "ERROR: Unlinking shared memory wasn't achieved: %s\n", strerror(errno));
            exit(1);
        }
    }
}

/**
 * Initialization of the mutex contorl mechanism, and validates if the shared memory object is available or
 * needs to be created.
 * 
 * @exception Launches a warn if the shared memory isn't available.
 * @exception Launches an error and exits if the shared memory region isn't created.
 * @exception Launches an error and exits if the shared memory wasn't truncated.
 * @exception Launches an error and exits if the shared memory mapping fails.
 * @exception Launches an error and exits if the mutex attributes init and set isn't achieved.
 * @exception Launches an error and exits if the mutex initialization fails.
 * @exception Launches an error and exits if the mutex attribute destruction wasn't possible.
*/
void init_mutex()
{
    // Open shared object in read/write mode to check if it exists
    mt_shm_fd = shm_open(MT_SHM, O_RDWR, 0600);
    if(mt_shm_fd >= 0)
    {
        mt_owner = 0;
        fprintf(stdout, "Mutex shared resources are available\n");
    }
    // If the mutex shared space isn't available, try to create.
    else if (errno == ENOENT)
    {
        fprintf(stderr, "WARN: Mutex shared resource isn't available\n");
        fprintf(stdout, "Now, creating mutex shared resources...\n");
        mt_shm_fd = shm_open(MT_SHM, O_CREAT | O_EXCL | O_RDWR, 0600);
        // Check creation of shared memory
        if(mt_shm_fd >= 0)
        {
            mt_owner = 1;
            fprintf(stdout, "Mutex shared resources have been created.");
        }
        else
        {
            fprintf(stderr, "ERROR: Couldn't created shared memory for mutex: %s\n", strerror(errno));
            exit(1);
        }
    }

    // If this process is the owner (creator), search for truncation of the region
    if(mt_owner)
    {
        if(ftruncate(mt_shm_fd, sizeof(pthread_mutex_t)) < 0)
        {
            fprintf(stderr, "ERROR: Couldn't truncate region for mutex: %s\n", strerror(errno));
            exit(1);
        }
    }

    // Map region in order to access to it, by using a generic pointer
    void* map = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, mt_shm_fd, 0);
    if(map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping region wasn't possible: %s\n", strerror(errno));
        exit(1);
    }

    // Get access to the mapped region, with the created mutex by using the generic pointer
    mt = (pthread_mutex_t*)map;

    // Create the contorl mechanism (mutex, with the respective attribute)
    if(mt_owner)
    {
        int status = -1;
        pthread_mutexattr_t attr;
        if((status = pthread_mutexattr_init(&attr)))
        {
            fprintf(stderr, "ERROR: Init attributes for mutex wasn't achieved: %s\n", strerror(errno));
            exit(1);
        }

        // Set shared resource, the flag PTHREAD_PROCESS_SHARED allows usage by multiple processes.
        if((status = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)))
        {
            fprintf(stderr, "ERROR: Setting attributes of mutex wasn't possible: %s\n", strerror(errno));
            exit(1);
        }

        if((status = pthread_mutex_init(mt, &attr)))
        {
            fprintf(stderr, "ERROR: Couldn't initialize mutex: %s\n", strerror(errno));
            exit(1);
        }

        if((status = pthread_mutexattr_destroy(&attr)))
        {
            fprintf(stderr, "ERROR: While destruction of mutex attribute: %s\n", strerror(errno));
            exit(1);
        }
    }
}

/**
 * Close the control mechanism (mutex) depending on the ownership and shared memory
 * 
 * @exception Launches warn if mutex isn't destroyed (in case of ownership)
 * @exception Launches error and closes if unmapping wasn't achieved
 * @exception Launches error and closes if file descriptor couldn't be closed
 * @exception Launches error and closes if unlinkig failed (in case of ownership)
*/
void shut_mutex()
{
    sleep(1);
    // If it is the owner, destroy the mutex.
    if(mt_owner)
    {
        int status = -1;
        if((status = pthread_mutex_destroy(mt)))
        {
            printf(stderr, "WARN: Mutex couldn't be destroyed: %s\n", strerror(errno));
        }
    }

    // Unmap memory region 
    if(munmap(mt, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping wasn't possible: %s\n", strerror(errno));
        exit(1);
    }

    // Close the mutex shared memory file descriptor
    if(close(mt_shm_fd) < 0)
    {
        fprintf(stderr, "ERROR: Couldn't close mutex: %s\n", strerror(errno));
        exit(1);
    }

    // Only if it is the owner, unlink the shared memory
    if(mt_owner)
    {
        if(shm_unlink(MT_SHM) < 0)
        {
            fprintf(stderr, "ERROR: Unlinking mutex wasn't achieved: %s\n", strerror(errno));
            exit(1);
        }
    }
}

/**
 * Check if the cancelation flag was raised, by implementing a secure way with mutex.
 * 
 * @return The value of the cancel flag
*/
int check_cancelation()
{
    pthread_mutex_lock(mt);
    int temp = *cancel_flag_ptr;
    pthread_mutex_unlock(mt);
    return temp;
}

/**
 * Launches in a secure way (by using mutex locks) the update of the cancel flag.
*/
void cancel()
{
    pthread_mutex_lock(mt);
    *cancel_flag_ptr = 1;
    pthread_mutex_unlock(mt);
}

/**
 * Handles an interrupt by printing the number of SIGINT received
 * 
 * @param sig Integer signal received in case of interruption
*/
void signal_handler(int sig)
{
    fprintf(stdout, "Integer value detected: %d\n", sig);
    cancel();
}