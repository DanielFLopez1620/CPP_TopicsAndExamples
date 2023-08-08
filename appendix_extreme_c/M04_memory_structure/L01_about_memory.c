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
 *    1418     544       8    1970     7b2   E1.o
 *        
 *    - BBS: Segment that relates with global declarations (remember, be selective with the goblal variables,
 *      as they introduce security concerns, concurrency issues, ownership problems, an others), but only 
 *      those with zero value or unititialized. For instance, the size output of E02_uninit_globals is:
 * 
 *       text    data     bss     dec     hex filename
 *       1418     544       8    1970     7b2 E2.o 
 * 
 *    - DATA SEGMENT: Storage those initialized global variables (non-zero value), you can see it with the 
 *    size compilation of the file E03_init_globals:
 * 
 *    text    data     bss     dec     hex    filename
 *    110       8       4     122      7a     E3.o
 * 
 *    Even, you can see the content of the data segment with the command:
 *         
 *        objdump -s -j .data <file.o>
 *    
 *    The flags are -s to show the respective selection section, -j for full content,
 *    and .data tells the section .data to appear.
 * 
 *    For example, with the file "E04_other_declaration", you can see:
 * 
 *        mem.o:     file format elf64-x86-64
 *
 *        Contents of section .data:
 *           0000 11000000 12233112 486f6c61           .....#1.Hola
 * 
 *    - ENDIANEES: It can be big-endian or little-endian, for the value 0x12153467
 *      the big endian 0x12153467 and the little endian is 0x7643521. It is just a 
 *      representation and both can be interpreted by C because it's a property of 
 *      a CPU.
 * 
 *    - TEXT SEGMENT: It contains all the machine-level instructions, and to see the
 *    content we will use 'objdump'. Let's experiment with a simple void C file 
 *    (E01_void_program.c):
 *     
 *        objdump -S <file.out>
 * 
 *      Then the output is:
 * 
 *      ex.out:     file format elf64-x86-64
 *
 *      Disassembly of section .text:
 *      0000000000000000 <main>:
 *      0:   f3 0f 1e fa             endbr64 
 *      4:   55                      push   %rbp
 *      5:   48 89 e5                mov    %rsp,%rbp
 *      8:   89 7d fc                mov    %edi,-0x4(%rbp)
 *      b:   48 89 75 f0             mov    %rsi,-0x10(%rbp)
 *      f:   b8 00 00 00 00          mov    $0x0,%eax
 *      14:   5d                      pop    %rbp
 *      15:   c3                      ret
 * 
 *      And you can use it to see the machine level instructions.
 * 
 *   - DYNAMIC MEMORY LAYOUT: Also called the runtime memory, the most important port is
 *     the loader, which can spawn process and create the initial memory. The process can 
 *     only exist after the two segments are created after the static one, they are the Stack 
 *     and Heap.
 *     
 *     - STACK SEGMENT: Default memory for variable (and small objects).
 *     
 *     - HEAP SEGMENT: Adjustable region of memory, focused on arrays and objects. But it
 *     would need an API.
 * 
 *     - MEMORY MAPPING: Just remember that '&' in a terminal command means "send it to background",
 *     it returns a PID (Process ID), which you can use to kill it. It allows to inspect the
 *     memory of a process.
 *       
 *     A memory mapping is a dedicated region which is mapped to a specific segment as part of a
 *     process. Usually, with a PID, you can find more about the process in the /proc/<PID> directory
 *     with the command:
 * 
 *         ls -l /proc/<PID>
 * 
 *     If we let run in the background the executable of the E05_mapping.c we can see:  
 *     
 *     dr-x------  2 root root 0 Aug  7 21:59 fd
 *     dr-x------  2 root root 0 Aug  7 22:03 fdinfo
 *     -rw-r--r--  1 root root 0 Aug  7 22:03 gid_map
 *     -r--------  1 root root 0 Aug  7 22:03 io
 *     -r--r--r--  1 root root 0 Aug  7 22:03 limits
 *     dr-x------  2 root root 0 Aug  7 22:03 map_files
 *     -r--r--r--  1 root root 0 Aug  7 22:03 maps
 *     -rw-------  1 root root 0 Aug  7 22:03 mem
 *     ....
 * 
 *     And we can access (or watch the content of some of them), of course with cat:
 * 
 *     cat /proc/<PID>/maps
 * 
 *     What I obtain is:
 * 
 *     55ca8bfbd000-55ca8bfbe000 r--p 00000000 08:10 107123                     /home/user/Documents/CPP_TopicsAndExamples/map.out
 *     55ca8bfbe000-55ca8bfbf000 r-xp 00001000 08:10 107123                     /home/user/Documents/CPP_TopicsAndExamples/map.out
 *     ...
 *     7fcf2c7e8000-7fcf2c7e9000 rw-p 00000000 00:00 0 
 *     7ffd5eaef000-7ffd5eb11000 rw-p 00000000 00:00 0                          [stack]
 *     7ffd5eb42000-7ffd5eb46000 r--p 00000000 00:00 0                          [vvar]
 *     7ffd5eb46000-7ffd5eb47000 r-xp 00000000 00:00 0                          [vdso]
 *     
 *     So, let's list the meaning of some of them:
 *     
 *     - Adress range: Start and end of the mapped range.
 *     - Permissions: R(read), w(modified) or x(executed), or s(shared) and p(private)
 *     - Offset: Positions it starts after a file or segment.
 *     - Device: Which or what contains the file (if attached to one).
 *     - Inode: Number of the file in the system (related with ext4 structure)
 *     - Description: Also known as the path, can be empty or can even specify the purpose
 *       of the segment (stack, for example).
 * 
 * 
 *   - STACK SEGMENT: Its content is usually changing, to watch those moves you will need
 *   a debugger (like gdb) to read the memory throug the process. The most common exception
 *   of it is "Stack Overflow" which mean it is full (and you may also recognize the word
 *   from a forum).
 * 
 *   The work of the stack is FILO (First In, Last Out) or LIFO (Last In, First Out). So,
 *   when using variables it is located on top and has to pop to see its content again, this
 *   also applies to local definitions.
 * 
 *   Function can be stacked but by the "stack frame", which put the function of top of the 
 *   segment to return after the execution. Here, you will need to make sure to avoid saturation
 *   of variables and prevent infinite recursion. 
 * 
 * NOTE: A debbugger attaches to a process and allows to process and identify the memory content.
 */    

int main(int argc, char *argv)
{
    printf("Do not forget to review the comments on the lesson...\n");
    printf("Also, try to run the commands with the example files to learn about memory...\n");
    return 0;
}
