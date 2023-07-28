// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>

/**
 * There are some types of obj formats, like:
 *   - ELF: Used mainly by Unix system, mainly those with Linux.
 *   - Mach-O: Used with OS X (Apple with macOS and iOS)
 *   - PE: Which is from Windows, from Portable Execution.
 * 
 * The precessor of all the outputs format was the a.out, which was replaced by
 * COFF, and then it a different version in different OS.
*/

int main(int argc, char **argv)
{
    printf("Do not forget to read the explanation...\n");
    printf("It's more about obj files format...\n");
    printf("Also, interesting resources here:\n");
    printf("- https://en.wikipedia.org/wiki/COFF#History\n");
    printf("- https://www.sco.com/developers/gabi/2003-12-17/ch4.intro.html\n");
    printf("- https://www.uclibc.org/docs/psABI-x86_64.pdf\n");

    return 0;
}
