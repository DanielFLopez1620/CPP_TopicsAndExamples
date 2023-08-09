// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Debugger: Program that links to processes to observe and manipulate memory. It can also be
 * used to control the order of execution. Our tool here is going to be'gdb'.
 * 
 * For using gdb you will need an executable, but it should contain debug info:
 *     
 *     gcc -g <file.c> -o <final>.out
 * 
 * Here the -g flag indicates that the compilation have to include debuggin info. It 
 * changes the size of the file, but it allows us to use 'gdb' in the future:
 * 
 *    gdb <final>.out
 * 
 * After running thew command, it should appear a log and '(gdb)' at the end. Here you
 * should write 'run' to launch the process... but wait, you will need breakpoints, which
 * is an indicator to pause in the line specified, for this you use 'b' or 'break' with
 * the argument of the word to stop, for example, main. To continue the execution of the 
 * debugger you use 'n' or 'next' command in the gdb terminal. 
 * 
 * An interesting feature is that you can see the memory in use, by using 'print <var>' or
 * even it relates to the stack, where you can print the allocation with 'x/4b <var'. The
 * number specify the registers considered (bytes). Also you can set variables with
 * 'set <var> = <value> here. 
 * 
 * Just remember to be careful as you still can smash the stack or prevent/avoid/change 
 * some definitions. In case of writing unchecked values into a buffer of the stack, it 
 * can be considered a exploit (buffer overflow attack) 
 * 
 * NOTE: 'gdb' is usually present in Linux systems, in case of macOS you will need to 
 * install it using brew or in windows manually install it.
 * 
*/

int main(int argc, char **argv)
{
    // Part for testing debugging with gbd:
    printf("L2: Simple test for gdb with arrays...\n");
    int nums[4];
    nums[0] = 1;
    nums[1] = 6;
    nums[2] = 2;
    nums[3] = 0;
    return 0;
}
