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
 * - sh_mem: Which is the class (parent class) for shared memory object, so you can initialize 
 *    and use them.
 * - counter: Class related with the objective to implement (counting) following POSIX standard.
 * - sh_mutex: Which is a child class from shared memory, with the option to create a shared mutex.
 * - sh_cv: Similar to the previous cases, but it the child of the sh_mem and sh_mutex classes.
*/

// Import for using the classes implemented with OOP in C
#include "L05_counter.h"
#include "L05_sh_mutex.h"
#include "L05_sh_cv.h"

int signal_rv = 0;
struct sh_cv_t* cv = NULL;
struct sh_mutex* mx = NULL;

void singal_handler(int signal);

int main(int argc, char const **argv)
{
    
    return 0;
}

void singal_handler(int signal)
{
    fprintf(stdout, "\nINT signal received: %d ...\n", signal);
    signal_rv = 1;
}
