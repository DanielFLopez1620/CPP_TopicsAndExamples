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
*/