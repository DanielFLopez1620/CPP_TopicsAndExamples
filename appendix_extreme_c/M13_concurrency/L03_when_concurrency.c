// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * If you can write a program with a single task, it is highly recommended. However, this is not
 * the case in most of the situations.
 * 
 * Althought you have a 'sequencial execution' (the next task needs to wait the previous one), but
 * they may take more or less time, so here is where you need to implement concurrency, as your PC
 * cannot only focus on your C code because it has more task to do.
 * 
 * You need to implement concurrency when one instruction can block the current flow, for example, 
 * those cases when you wait the user response. So, it is better to divide your tasks and keep present
 * the ones that can block the flow.
 * 
 * STATES: A task is usually linked to a 'overall state'  that corresponds to the exisiting values and 
 * process linked to the task at some point of been executed. Also, we have 'intermediate states' that is
 * when part or certain instructions have been executed. But, we can also have 'shared states' which
 * is a set of variables with some values at a specific time of a concurrent task, it is not owned by
 * itself and can be read/modified. This is related that a C command can have (inside it) divided task to
 * make it concurrent or is composed of 'atomic instructions', so for a concurrent system, you will need 
 * to divide task that take advantage of atomic instructions and do not block the processor.
 * 
*/

int main(int argc, char **argv)
{
    printf("This section was mainly informative, but you can check on internet more about concurrency\n");
    printf("Good luck!\n");
    return 0;
}
