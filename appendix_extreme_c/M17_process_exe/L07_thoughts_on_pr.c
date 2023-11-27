// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * There are a lot of topics to cover when using process. But let's talk about files and
 *  multithreading.
 * 
 * * POSIX FILE SYSTEM: For managing files, there is a need on file descriptors, for example,
 *   'ext4'. As you know, you can open, read, write and close files with the correct file
 *   descriptor.
 * 
 *   But you need to know the difference between a file object in memory and a shared memory
 *   object, keep in mind:
 *   - A file is located on the disk, while a shared memory is in the memory space of the
 *     kernel.
 *   - Shared memory will be rebooted with the system, but files retain info.
 *   - Accessing to a shared memory is faster than accessing to the filesystem.
 *   
 *   You can change the space or usage of shared memory to filesystem in a very simple way,
 *   you just need to make the substitions:
 * 
 *      shm_opn("/shm0", ...)  -->  open("file.ext", ...)
 *      shm_unlink(shared_fd)  -->  remove("file.ext")
 * 
 * * MULTITHREADING VS MULTIPROCESSING: 
 *   - MULTITHREADING: If you have a fat process (that does everything) and you have many
 *     requests, you will need to use a multithreaded approach so you can handle multiple 
 *     requests, but keeping the a certain number of threads, so you do not end doing a 
 *     'vertical scaling'.
 *   - SINGLE HOST MULTIPROCESSING: Multiple process in a single machine, and they can have
 *     one or multiple threads. In this case you will need more processes ending with  a 
 *     'horizontal scaling'. Here the process are running concurrently, but it may not be 
 *     effective.
 *   - DISTRIBUTED MULTIPROCESSING: Multiple processes running in different host and they are
 *     connected to the network. This allows scalation without limits. The key here is to 
 *     search for less latency, more fault tolreance, more availability and more data
 *     consistency.
 *   
*/

int main(int argc, char const *argv[])
{
    
    printf("Here you can find a list of resources regarding this situation:\n");
    printf("\t- Zero-Copy receive mecahnism: https://lwn.net/Articles/752188/\n");
    printf("Do not forget to check on internet if you want to learn more.\n");
    return 0;
}
