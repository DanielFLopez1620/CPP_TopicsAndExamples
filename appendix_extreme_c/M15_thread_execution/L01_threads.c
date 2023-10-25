// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * THREADS: They are initiated by a process and will be linked forever (or at least until the process die), but each process
 * must have a 'main thread' in the case of this code, it will be the 'main' function. Also, there would be a Process ID (PID) 
 * that would belong to the threads (check them with 'top' or 'htop' commands), but each thread has a unique Thread ID (TID) 
 * and they are accesible via the pthread_t variable and has a mask signal to check what the thread recieves. For transfering
 * or sharing a state they can:
 * 
 *  - Own process memory.
 *  - Use the filesystem.
 *  - Memory-mapped files.
 *  - Share memory.
 *  - Use POSIX pipes and queues.
 *  - Set and get environment variables.
 * 
 * The lifetime of a thread is linked to its owner process, but they must be ended before the process is terminated. Also, the 
 * threads can vary and be related with the kernel (kernel-level, related with logic and higher priorities, also they have 
 * access to the kernel memory space) or the user (user-level, but they cannot be created directly).
 * 
 * Do not forget the synchronization techniques (semaphores, mutexes and conditions) so you don't get data race or race condition
 * and you get a 'thread-safe program'.
*/

int main(int argc, char **argv)
{
    printf("Read the comments of this lesson to get an intro about threads...\n");
    printf("Also, here a info related with POSIX threads:");
    printf("https://man7.org/linux/man-pages/man7/pthreads.7.html\n");
    return 0;
}
