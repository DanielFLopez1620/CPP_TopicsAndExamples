// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * You will always find bugs, or error in tests, then you need to find a bug... but how? Well this
 * involves a lot of sessions of debugging (word that comes when the computers were so big that
 * you will usually find literally bug like mocks in the system machinery leading to malfunctions),
 * but again, debugging isn't only about running the code slower, you will have to consider more
 * things.
 * 
 * After all, a program can be thought as a black box, and with debuggers you can check the code 
 * step by step and focus your attention in the results generated.
 * 
 * When building a program, you have two different results: Release (focused on executon and
 * functionality, program as a black box) and build (which allows to trace all the events), and here
 * you can also have debug builds useful for development and testing. To make the last one possible,
 * you need a 'debugging symbol' which allows the user to see the 'stack trace'.
 * 
 * But... why do we need to use debuggers if a debug build allow to trace the events? Debuggers
 * mission is to attach the target process to control and monitor it. But they aren't the unique
 * tool for debugging as you can study the memory, the concurrent execution and performance.
 * 
 * Luckily, most of the bugs are reproducible, but you have to keep in mind that some of them may
 * not appear in debugging sections due to the observer effect which says "If you want to look
 * at the internal of a program, you alter the way you see it working which may be prevent the 
 * bugs from appearing".
 * 
 * BUG CATEGORIES:
 * 
 * - Logical bugs: They require understading on the flow of the program. And it can be checked or
 *   discovered by tracing the executing flow.
 * 
 * - Memory bugs: Usually related with dangling pointers, buffer overflow, double frees or related,
 *   for this, you will need a 'memory profiler' to monitor the memory.
 * 
 * - Concurrency bugs: The hardest bugs, related with multi-processing and multithreading, for
 *   this it is uselful to have a 'thread snaitizer' to detect race conditions and data races.
 * 
 * - Performance bugs: Adding functions and proceses may result in performance degradation, here a
 *   solution can be a checking by using logs.
 * 
 * DEBUGGERS: Do not forget about 'gdb', but we need more looks to this topics, firts let's mention
 * some of the features that a debugger have:
 * 
 * - It is a program that attachto another process given the target process ID.
 * - It can contorl the execution of the instructions in the target process, then it also provides
 *   to the user the option to control the flow.
 * - Debuggers have tha ability to see the protected memory of a process.
 * - They can related the debugging symbol with the instruction in the source code.
 * - If the debugging symbol isn't provided, it can generate a disassembly code of the instruction.
 * - They are focused mainly in a specific languages.
 * 
 * Now, let's give some honored mentions of debuggers:
 * 
 * - adb (Advanced Debugger): Unix debugger.
 * - gdb (GNU Debugger): GNU version of the Unix Debugger.
 * - LLDB: Designed for debugging file objects produced by LLVM.
 * - Python Debugger: For Python scripts.
 * - JPDA (Java Platform Debugger Architecture): ApI for debugging inside a JVM instance.
 * - OllyDBG: For Microsoft Windows debugging of GUI applications.
 * - Microsoft Visual Studio Debugger.
 * 
*/

int main(int argc, char** argv)
{
    printf("Here you can find some useful resources:\n");
    printf("\t- https://en.wikipedia.org/wiki/Debugging\n");
    printf("\t- https://en.wikipedia.org/wiki/List_of_debuggers\n");
}