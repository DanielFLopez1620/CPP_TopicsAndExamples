// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Although Multics was revolucionary, more steps were done forward a better OS.
 * 
 * The philosophy of the change (UNIX) includes:
 * - Unix is designed and developed to be used by programmers.
 * - Keep many small and single programs, for small and single tasks.
 * - A complex task can be perfomed by a group of small and simple programs.
 * - The output of one program should be able to be used in aonther program.
 * - Unix is text oriented
 * - Always simplicity over perfection.
 * - A UNIX program should be easily usable in another Unix.
 * 
 * Now, let's tal about the structure, the onion (User Apps (Shell (Kernel (Hardware)))), so the layers:
 * 
 * - HARDWARE: The OS must have the ability to interect and use the hardware, as it is the core of all working things here.
 * - KERNEL: The most important part of a OS, is a wrapper to expose the functionalities of the hardware, so it has the 
 *   higher privilige (in terms of resources).
 * - SHELL: Allows the user to interact with the Kernel. It contains small programs that respond to a single task, but they 
 *   can be combined to generate a complex interaction.
 * - SIMPLE UNIX SPECIFICATION: It is the close defined interface for the programmer.
 * - USER APPLICATION: The apps of the OS that are related with the user and what he wants to do, like web browsers, editors,
 *   among others.
 * 
 * They key for interaction is a 'human interface' that can be a terminal (CLI, Command Line Interface) or a GUI (Graphical User Interface),
 *  they allow the control of the hardware by using the shell ring, so there must be an API (Application Programming Interface) provided.
 * 
 * Think an API as a group of header files with declarations that can be used, so there is a standard way to
 * use them in Unix system but each Unix-compliant system can has some differences in its static and dynamic libraries. As a
 * standard, Unix has this UNIX compliant systems and UNIX-like systems (Linux).
 * 
 * CURIOSITY: printf is not part of C, it is part of the SUS (Simple Unix Specification) standard contained in the 
 * C standard library.
 * 
 * The SUS standart (V4), has a list of APIs related to:
 * - System Interfaces: Function that should be used in any C program.
 * - Header Interfaces: List of campatibles systems, some of them are stdio.h and stlib.h.
 * - Utility interface: For utilitys and command line programs (your terminal toolkit).
 * - Scripting interface: For shell scripting and task automation.
 * - XCURSES interfaces: For interaction between C and minimalist GUI.
 * 
 * But... what about filesystems and the places where those headers are found? For that exits a convention that is:
 * "All headers must be found in /usr/include or /usr/local/include".
 * 
 * And for the usage, exist the C Standar Library or libc that is a set of functions together with 
 * the implementation of the exposed functions (by respecting SUS). But, after the creating of many
 * Unix-like OS, appear a subset of SUS called Portable Operating System Interface (POSIX), now Linux Distros
 * are POSIX-compliant.
 * 
 * Another possibility is to interact with the kernel with libc (just in case, if you want to create your
 * Unix, your will need to create your own libc after having the kernel ready). A key for this is having 
 * a compilation pipeline and a linking mechanism so it can expose the interace. For using the kernel functionalities,
 * it is used the 'system calls'.
 * 
 * One interesting header is 'unistd.h' which can call SUS exposed interaces, like 'sleep(<time>)' command, but
 * what is behing those common functions you use (pirntf, malloc...). First, we have to know that
 * exist a pgrogram that traces when a program is running, and second that the 'syscalls' are triggered, we can
 * check this by compiling the code and checking the triggers:
 * 
 *  gcc <file.c> -lc -o <file.out>
 *  truss ./<file.out> # Only in FreeBSD
 * 
 * Here 'truss' is used to traces sys calls, its equivalent in Linux is 'strace'. And here you can check
 * the call and the links generated in the process (or with th executable). You an think of syscalls as function
 * calls, as they have an indicator and have a list of arguments. If you asked, the -lc option in the previous
 * command is for linking in FreeBSD.
 * 
 * TIP: You can use 'man' command on terminal to access the manual of a command or even trigger/syscall.
 * 
 * Now, let's talk about the Kernel, as you already know, it is used for managing the hardware. But the 'kernel
 * processes' are very different from the 'user processes' you know. In one hand, a kernel process is first
 * executed and loaded, the hardware can run only a single of them, it is created by copying the kernel
 * image into the memory by the boot loader and it handles system calls. On the other hand, a user process doesn't
 * have priviliges, needs a kernel process runing, many of them can be executed at the same time and they call the 
 * syscalls.
 * 
 * The previous means that there are two execution modes: Kernel land or space (for kernel processes) and the user
 * land or user space, and they need to be isolated, so one tool for achieving this was 'syscalls'. Now, let's look
 * at the kernel task in Unix:
 * 
 *  - PROCESS MANAGEMENT: Allocation memory, loading instructions and other process related to sys calls.
 *  - INTER-PROCESS COMMUNICATION (IPC): Cover data exshange with memories, pipes and domains.
 *  - SCHEDULING: Management of the CPU cores and balances the task there.
 *  - MEMORY MANAGEMENT:  Without memory, the processes would be lost.
 *  - STARTUP: Load image kernel, and then start kernel process, then user processes using PID (Proccess Identifier)
 *  - DEVICE MANAGEMENT: It includes ports, USB devices, adapters...
 * 
 * Finally, we have the HARDWARE, the purpose of the interaction for using different utilities. The hardware is threated
 * as a number of devices attached which can be 'mandatory' (CPU & memory) or 'peripheral'. The Memory Management and the 
 * Scheduler units are responsible for the mandatory decices. But the others are exposed 'device files' in the folder /dev. 
 * 
 *     ls -al /dev
 * 
 * This allows you to even have 'virtual devices'
*/

int main(int argc, char** argv)
{ 
    printf("Here a list of useful resources:\n");
    printf("\thttps://kukuruku.co/post/the-collapse-of-the-unix-philosophy/\n");
    printf("\thttps://www.linfo.org/unix_philosophy.html\n");
    printf("\thttps://en.wikipedia.org/wiki/Unix_philosophy\n");
    printf("\thttp://www.unix.org/version4/GS5_APIs.pdf\n");
    printf("\thttps://pubs.opengroup.org/onlinepubs/9699919799/\n");

    return 0;
}
