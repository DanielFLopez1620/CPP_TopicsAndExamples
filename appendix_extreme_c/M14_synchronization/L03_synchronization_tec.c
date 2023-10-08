// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Some techniques will be needed in order to mantain the invariant constraints and keep the concurrency working,
 * so there are 'happens-before' constraints that keep the order of execution between tasks.
 * 
 * - BUSY-WAITS AND SPIN LOCKS: It is a complex form of saying that a task needs to wait after another task in order
 *   to begin. 
*/

int main(int argc, char const *argv[])
{
    printf("Example 1: Without busy-wait mechanism:\n");
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
    
    
    return 0;
}
