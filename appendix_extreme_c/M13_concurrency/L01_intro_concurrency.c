// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * CONCURRENCY: Having multiple parts of a code running "simultaneously". It means that you
 * can have different task running at the same time, for example, the act of writting in 
 * Microsof Word implies the write task, while including grammar and ortography checks.
 * 
 * Keep in mind.... Being concurrent is different from being parallel.
 * 
 * This concept is not exclusive of C, and can be done with multiple languages...
 * Some key concepts are 'task', 'schedulind', 'state' and others.
 * 
 * PARALLELISM: Running two or more task at the same time, they are really happening simultaneously
 * while in concurrency, you need to pause one to let another be executed.
 * 
 * In computer systems, CPUs have cores inside of them, if you have 2, you can run two parallel task.
 * If you need to do more task, you will need to break them in steps and specify some time for each
 * one.
 * 
 * TASK SCHEDULER: Concurrency is like multitasking, but you will need a 'task scheduler', its function is to switch 
 * task very quickly which creates an artificial parallelism. It works with a queue of task that are waiting
 * for some space to work and it is prioritized (high priority first); this means that they have an order but
 * the moment one finishes using the CPU (or a time quantum is completed), another task is send. Finally, it must
 * be able to recover the CPU control in case of preemptive task or scheduling.
 * 
 * But ... What is a task? It is an abstract concept of a process that needs to be done. They are categorized
 * according to its importance and added to a wait list, you they will get a turn with the processor. But the task
 * can be divided in two groups (process or thread). But before that keep in mind that switching 
 * between task is not predictable, so you will have to assume the probability of having a certain context...
*/

int main(int argc, char **argv)
{
    printf("This section's comments are an intro to CONCURRENCY.\n");
    return 0;
}
