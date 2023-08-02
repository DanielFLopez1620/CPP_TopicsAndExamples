// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>

/**
 * NOTE: Memory management in C/C++ is the responsability of the programmer, and it implies optimization,
 * security and effectiveness.
 * 
 * PROCESS MEMORY LAYOUT: Running an executable converts it in a 'process', something that has memory
 * and is using resources of the CPU, each process has an unieque Process Identifier (PID), it will remain
 * running until it finish the task or is stopped by someone/something like SIGTERM (Signal Termination, 
 * which allows clean up), SIGINT(Signal interrupt, like CTRL+C in Unix) and SIGKILL (Signal Kill, for 
 * those who need something powerful to be stopped). The process is divided in different parts called 
 * 'segments' some of them are Block Started by Symbol BSS, Data segment, Text Segment, Stack and Heap.
 * 
 * MEMORY STRUCTURE: Remember a proccess consumes a region of memory and the CPU is working with him
 * (mainly by freching and executing instructions), so the memory has different layouts (former is static
 * and latter is dynamic). To see the memory content of a file you can use the command 'size', just notice 
 * that the response/output of it would be different depending on you OS.
 * 
 *  - STATIC MEMORY LAYOUT: For this we need to experiment, first we a minimal C file (E01_void_program.c) 
 *    compiled, its content seems to be: 
 *    
 *    text    data     bss     dec     hex   filename
 *    1418     544       8    1970     7b2   E0.o
 *        
 *    - BBS: Segment that relates with global declarations (remember, be selective with the goblal variables,
 *      as they introduce security concerns, concurrency issues, ownership problems, an others), but only 
 *      those with zero value or unititialized.
 */

int main(int argc, char *argv)
{
    printf("Do not forget to review the comments on the lesson...\n");
    printf("Also, try to run the commands with the example files to learn about memory...\n");
    return 0;
}
