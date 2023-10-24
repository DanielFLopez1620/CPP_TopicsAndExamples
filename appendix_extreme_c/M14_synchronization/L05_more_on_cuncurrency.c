// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * The kernel allows the possibility of concurrency and multitasking.
 * 
 * In the case of UNIX, POSIX tried to standardize the API exposed and this standard included
 * concurrency a long time ago, then this was passed to Linux and macOS. But this implies two 
 * possibilities, on one hand multi-processing (a concurrent program executing at different 
 * processes) or on the other hand, we have multithreading(a program running at different 
 * threads as part of one process).
 * 
 * One of the key parts of the process is the 'task schduler unit' which share an important role
 * with the CPU for running processes and threads. But what are the differences bewteen these two:
 *  
 * - Processes: Isolated form one another, so they do not have access between them.
 * - Threads: Used to bring concurrency into a process by having many of them executing intructions,
 *   and they are local to a process.
 * 
 * But they are mainly refered as 'tasks' and the kernel see them as a list/queue of task waiting
 * for some time with the CPU. This implies some strategies for scheduling a task, we have Cooperative
 * Scheduling (Give the CPU a task and wait cooperation, leaving the core at some point) and Preemtive 
 * Scheduling (A task has time with the CPU until the scheduler take it back, this given time is called
 * time slice or quantum). The last one is the most used in kernels and there are many types, one of them
 * is 'round robin' which is based in a starvation-free access to a shared resource, and it can be
 * modified to implement priorizations.
 * 
 * * MULTI-PROCESSING: Using processes to do concurrent task, for example, with CGI (Common Gateway Interface)
 *   which means that a new HTTP request launch a new 'interpreter process' so it can manage simultaneous
 *   requestst.
 *   These process needs to share a lot of information  to keep the cluster running and this implies
 *   distribuited systems. And when there is a shared state the complexity increases.
 *   Now, remember that a process has a private memory, so sharing is difficult. With this said, let's mention
 *   some techniques:
 * 
 *   - FILE SYSTEM: Leave something in memory, so simple. 
 *   - MEMORY-MAPPED FILE: Some regions can be used by a certain number of processes to share info (read/modify).
 *   - NEWTWORK: For process that are in different computers.
 *   - SIGNALS: A way to communicate between processes or to share small states.
 *   - SHARED MEMORY: A region that is shared by multple processes and can be used by all of them.
 *   - PIPES: One-way communitacion, one publish and the other hears and subscribe.
 *   - SOCKETS: Information over a full-duplex channel which is fast.
 *   - MESSAGE QUEUE: Messages maintained in the kernel so the process only access there.
 *   - ENV VARIABLES: Varialbles kept in the OS and can be accessed by process within the system.
 * 
 * * MULTITHREADING: Using threads to perform parallel task and a thread is always owned by a process. They
 *   can use the previous techniques mentioned with the advantage of having  access to the same memory region.
 *   Which means they have their own Stack and here the shared states can be kept, also a address can be passed
 *   to other thread which it can use to get access.
*/

int main(int argc, char const *argv[])
{
    printf("Read the comments of this codes to get to know more about concurrency\n");
    printf("You will discover about multi-processing and multithreading!\n");
    return 0;
}
