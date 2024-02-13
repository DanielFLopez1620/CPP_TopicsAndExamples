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
 * MEMORY PROFILER: As we mention before, you can also find bugs related with memory, for this, you
 *  can take advantage of memory chackers to prevent bugs, sometimes it is integrated with the 
 * debugger, but it can be also provided as a separete program, some of its features are:
 * 
 * - Reporting memory allocated, freed memory, stack and heap allocations.
 * - Detection of memory-leak situations.
 * - Detection of invalid write/read operations.
 * - Report on double frees.
 * 
 * We have focused only on 'memcheck' (a valgrind tool) but there are more, they can be agrupated
 * as:
 *  - Compile-time overriding:  This will imply modifiying your source code and add the checker
 *    library, then to comile again and link the library, it isn't invasive in performance but
 *    implies an additional compiliation. Examples are: LLVM AdressSanitizer (ASan), Memwatch,
 *    Dmalloc and Mtrace.
 * 
 *  - Link-time overriding: Here you do not need changes, you just need to link the binaries with
 *    library. The most well-know tool is 'heap checker' from 'gperftools'.
 * 
 *  - Runtime interception: AS the name says, it intercepts (or at least try) and track all memory
 *    related operations and report of invalid access, the main advantage is that you do not need
 *    to recompile, but it introudces an overhead in the execution and will need more resources. 
 *    Memscheck can be used for this purposes, but it shouldn't be used while having a debugging
 *    base.
 * 
 *  - Preloading libraries: Another method used is wrapping standard memory functions, as they uses
 *    'LD_PRELOAD' environment variables, 'heap checker' can achieve this function.
 * 
 * THREAD DEBUGGERS: It is usually a must need when having a concurrency program which may lead
 * to concurrency issues which can be data races, misusing threadin API, deadlock and lock ordering
 * issues. Keep in mind that sometimes exists 'false positives' cases, depending on the tool you
 * are using, but it also should consider your opinion on the matter.
 * 
 *  - Helgrind: Provided by Valdgrind for thread debugging. Check the resources below to see its
 *    capabilities. Remember you can use helgrind with the command:
 * 
 *          vlagrind --tool=helgrind <path_to_file>
 * 
 *  - Intel Inspector: Successor of Intel Thread Checker acts like a thread debugger with 
 *    integrated memory checker. But you need a pay license.
 * 
 *  - LLVM ThreadSanitizer (TSan), as part of LLVM, can be used for this purpose, but you will need
 *    some slight compile-time modifications.
 * 
 * PERFORMANCE PROFILERS: Degradation of performance can be an issue when modifying a code, and you
 * can collect specialized info for this purpose, which can be:
 * 
 *  - Gather statitistics about function calls.
 *  - Trace call functions.
 *  - Collect lock contention and allocation/deallocation statistics.
 *  - Cache analysis
 *  - Gather statistics abouts thread events.
 * 
 * Some tools you can use are:
 * 
 *  - Google Performance Tools (gperftools): Provides a performant malloc implementation, but it
 *    doesn't stop here, as you can also use the heap checker by linking the final binary.
 * 
 *  - Callgrind (part of Valgrind): Which focuses on statistics for function calls and the relation
 *    of caller/calle response.
 * 
 *  - Intel VTune: Provides all the features mentioned before but for a price of a license.
 * 
*/

int main(int argc, char** argv)
{
    printf("Here you can find some useful resources:\n");
    printf("\t- https://en.wikipedia.org/wiki/Debugging\n");
    printf("\t- https://en.wikipedia.org/wiki/List_of_debuggers\n");
    printf("\t- http://valgrind.org/docs/manual/hg-manual.html\n");
    printf("\t- http://valgrind.org/docs/manual/drd-manual.html\n");
}