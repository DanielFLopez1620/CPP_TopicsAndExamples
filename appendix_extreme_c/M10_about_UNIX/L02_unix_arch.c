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
 * CURIOSITY: printf is not part of C, it is part of the SUS standard contained in the C standard library.
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
 * the implementation of the exposed functions (by respecting SUS).
*/

int main(int argc, char** argv)
{ 
    printf("Here a list of useful resources:\n");
    printf("\thttps://kukuruku.co/post/the-collapse-of-the-unix-philosophy/\n");
    printf("\thttps://www.linfo.org/unix_philosophy.html\n");
    printf("\thttps://en.wikipedia.org/wiki/Unix_philosophy\n");
    printf("\thttp://www.unix.org/version4/GS5_APIs.pdf\n");

    return 0;
}
