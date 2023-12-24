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
 * 
 * For using the code present here in the lesson five, you need to run:
 * 
 *      gcc -c L05_sh_mem.c -o sh_mem.o
 *      gcc -c L05_counter.c -o counter.o
 *      gcc -c L05_sh_mutex.c -o sh_mx.o
 *      gcc -c L05_sh_cv.c -o sh_cv.o
 *      gcc -c L05_named_condvar.c -o main.o
 *      gcc sh_mem.o counter.o sh_mx.o sh_cv.o main.o lpthread -lrt -o cv_test.out
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Import for using the classes implemented with OOP in C
#include "L05_counter.h"
#include "L05_sh_mutex.h"
#include "L05_sh_cv.h"

int signal_rv = 0;
struct sh_cv_t* cv = NULL;
struct sh_mutex_t* mx = NULL;

void signal_handler(int signal);

int main(int argc, char const **argv)
{
    signal(SIGINT, signal_handler);

    if (argc < 2)
    {
        fprintf(stderr, "ERROR: Argument needed: Process Number.\n");
        exit(1);
    }

    int goal = atol(argv[1]);
    printf("My goal is: %d\n", goal);

    struct shared_counter_t* counter = shared_counter_new();
    shared_counter_ctor(counter, "/counter0");
    shared_counter_setvalue_ifowner(counter, 1);

    mx = sh_mutex_new();
    sh_mutex_ctor(mx, "/mutex0");

    cv = sh_cv_new();
    sh_cv_ctor(cv, "/cond0");

    sh_mutex_lock(mx);

    while(shared_counter_getvalue(counter) < goal)
    {
        printf("Counter: %d", shared_counter_getvalue(counter));

        if(signal_rv)
        {
            break;
        }
        printf("Waiting fo signal, timeout is 5 seconds...\n");
        sh_cv_timedwait(cv, mx, 5L * 1000 * 1000 * 1000);

        if(signal_rv)
        {
            break;
        }
        printf("Checking condition... \n");
    }
    if(signal_rv)
    {
        printf("Exiting program...\n");
        sh_mutex_unlock(mx);
        goto destroy;
    }

    shared_counter_setvalue(counter, goal + 1);
    printf("Now turn for: %d\n", goal);
    sh_mutex_unlock(mx);
    sleep(1);
    sh_cv_broadcast(cv);

destroy:
    sh_cv_dtor(cv);
    sh_cv_delete(cv);

    sh_mutex_dtor(mx);
    sh_mutex_delete(mx);

    shared_counter_dtor(counter);
    shared_counter_delete(counter);

   return 0;
}

void signal_handler(int signal)
{
    fprintf(stdout, "\nINT signal received: %d ...\n", signal);
    signal_rv = 1;
}
