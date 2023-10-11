// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Some techniques will be needed in order to mantain the invariant constraints and keep the concurrency working,
 * so there are 'happens-before' constraints that keep the order of execution between tasks.
 * 
 * - BUSY-WAITS AND SPIN LOCKS: It is a complex form of saying that a task needs to wait after another task in order
 *   to begin. But this isn't optimized, as it implies a wait time that could be used in another task.
 * 
 * - SLEEP/NOTIFY MECHANISM: It notifies a task when its state is completed, and it is considered base in many OS. Look
 *   at examples 3 and 4 below.
 * 
 * - SEMAPHORES AND MUTEX: The first concept was an invention of Edsger Dijkstra while he develop "THE Multiprogramming
 *   System", and its refered to using simple variables to sunchronize access to a shared resource. They work with queue
 *   lists and they are a line for a 'critical section', watch example 5. The second concept refers to mutual exclusion, 
 *   as only one can enter to the critical section, no deadlock should exist and it should be collaborative and it's one
 *   of the basis of concurrency.
 *   Knowing this, you can create locking and unlocking algorithms, you can see example 6 below. So it implements a
 *   'contention' and it implies a 'contention time' (time to acquire lock).
 * 
 * - MULTIPLE PROCESSOR UNITS: When you have only one core, you usuallly can take advantage of a 'local cache' where some
 *   adresses are stored, which also reduces the time spen with the main memory. This even exists when there are multiple 
 *   cores. But when this happen, what must one prevent? Because there would be cases when there is an update in the cache 
 *   but not in memory and then a shared resource problem will appear.
 *   However, for this reason, the 'memory coherence protocol'  
 *   
 * 
 * - 
*/

int main(int argc, char const *argv[])
{
    printf("Example 1: Without synchronization mechanism:\n");
    printf("System\n");
    printf("{\n");
    printf("    Task A\n");
    printf("    {\n");
    printf("        printf(\"Hello!\");\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        printf(\"World!\");\n");
    printf("    }\n");
    printf("}\n\n");

    printf("Example 2: With busy-wait mechanism:\n");
    printf("System\n");
    printf("{\n");
    printf("    Shared State\n");
    printf("    {\n");
    printf("        int done = 0;\n");
    printf("    }\n");
    printf("    Task A\n");
    printf("    {\n");
    printf("        printf(\"Hello!\");\n");
    printf("        done = 1;\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        while (!done) {}\n");
    printf("        printf(\"World!\");\n");
    printf("    }\n");
    printf("}\n\n");

    printf("Example 3: With sleep/notify mechanism:\n");
    printf("System\n");
    printf("{\n");
    printf("    Task A\n");
    printf("    {\n");
    printf("        printf(\"Hello!\");\n");
    printf("        notify(B); // Invented notification with C\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        if(notification)\n");
    printf("        {\n");
    printf("            printf(\"World!\");\n");
    printf("        }\n");
    printf("    }\n");
    printf("}\n\n");

    printf("Example 4: With sleep/notify mechanism improved:\n");
    printf("System\n");
    printf("{\n");
    printf("    Shared State\n");
    printf("    {\n");
    printf("        int done = 0;\n");
    printf("    }\n");
    printf("    Task A\n");
    printf("    {\n");
    printf("        done = 1;\n");
    printf("        printf(\"Hello!\");\n");
    printf("        notify(B); // Invented notification with C\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        while(!notification)\n");
    printf("        {\n");
    printf("            atomic_sleep(); // Another invented routine for learning purposes.\n");
    printf("        }\n");
    printf("        printf(\"World!\");\n");
    printf("    }\n");
    printf("}\n\n");
    
    printf("Example 5: With semaphore mechanism:\n");
    printf("System\n");
    printf("{\n");
    printf("    Shared State\n");
    printf("    {\n");
    printf("        int con = 0;\n");
    printf("        s = semaphore(1); // Allow one task");
    printf("    }\n");
    printf("    Task A\n");
    printf("    {\n");
    printf("        enterCriticalSec(s);\n");
    printf("        a = con;\n");
    printf("        a = a + 1;\n");
    printf("        con = a;\n");
    printf("        exitCriticalSec(s);\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        enterCriticalSec(s);\n");
    printf("        b = con;\n");
    printf("        b = b + 2;\n");
    printf("        con = b;\n");
    printf("        exitCriticalSec(s);\n");    
    printf("    }\n");
    printf("}\n\n");

    printf("Example 6: With locking semaphore mechanism:\n");
    printf("System\n");
    printf("{\n");
    printf("    Shared State\n");
    printf("    {\n");
    printf("        int con = 0;\n");
    printf("        s = semaphore(1); // Allow one task");
    printf("    }\n");
    printf("    Task A\n");
    printf("    {\n");
    printf("        lock(s);\n");
    printf("        a = con;\n");
    printf("        a = a + 1;\n");
    printf("        con = a;\n");
    printf("        unlock(s);\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        lock(s)\n");
    printf("        b = con;\n");
    printf("        b = b + 2;\n");
    printf("        con = b;\n");
    printf("        unlock(s)\n");    
    printf("    }\n");
    printf("}\n\n");
    
    return 0;
}
