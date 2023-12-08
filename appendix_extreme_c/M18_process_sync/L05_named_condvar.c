// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * For multi-processing systems, we need to allocate the condition variable in a shared memory
 * region, and every condition variable should come with a mutex, this implies the usge of three
 * shared memory regions. 
 * 
 * NOTE: You can create a single shared memory by using an structure. And we can improve its
 * management with a OPP approach. So for this lesson, check the code divided in the files for
 * implementing the clases:
 * 
 *  - 
 * 
*/
