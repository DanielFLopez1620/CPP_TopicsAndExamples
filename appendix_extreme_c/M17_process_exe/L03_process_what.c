// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * After checking about process creation and execution, you must remember the following:
 *
 * - When using 'fork' there would be two process at the end, but 'exec*' end with one (a substituion).
 * - By using 'fork' you duplicate the memory content, but with 'exec*' you destroys the layout and
 *   create a new one.
 * - The forked process knows something about its parent, but the 'exec*' process do not have any idea.
 * - With 'exec*' you can run scripts and executables, but with 'fork' you can only create process.
 * 
 * You can undestand the 'fork' process like a clonning rather than executing something. And keep in
 * mind that by using 'exec' there is a call to the kernel, which tries to find a handler for the file
 * and then load the contents. It also has to consider if the permissions of execution are valid, then 
 * allocates de memory, generate a copy, prepare the memory mappings, create the main thread, initialize
 * the vital register and execute the instructions.
*/

int main(int argc, char **argv)
{
    printf("Read the comment of the codes to understand the difference between...\n");
    printf("\tPROCESS CREATION and EXECUTION\n");
    printf("If you want to check more info on this topic, check the link below:\n");
    printf("\t- https://lwn.net/Articles/631631/ and https://lwn.net/Articles/630727/\n");
    return 0;
}
