// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc, and there is a possibility it doesn't work or lead to a crash

#include <stdio.h>

/**
 * You can also use 'exec*' functions to execute a new process, which are based on first creating 
 * a simple process and then load a target process (a process image) which is a loaded version of
 * an executable. In other words, it is a process substitution.
 * 
 * Check the example 1 below to discover an 'echo' implementation. But note that the 'exec' functions
 * can also execute ELF files, scripts and binary files (a.out).
 * 
 * There are more functions for this matters:
 * 
 * - execl: Receive an absolute path to an executable, and call it with the args passed.
 * - execlp: Receives a relative path to an executable, and call it with the arguments used.
 * - excele: Like the execl, but accepts environmental variables.
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    printf("Example 1: Creation of a simple echo process: \n");
    
    // Creating a call of a linux command to start a new process
    char *args[] = {"echo", "This", "is", "a", "New", "Process", 0};
    execvp("echo", args);

    // If the process creation goes right, it should start a new process and forget the rest
    printf("Creation of echo process went wrong\n");

    return 0;
}