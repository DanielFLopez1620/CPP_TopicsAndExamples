// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * fopen has different uses with files (not all in the filesystem), for example:
 * 
 *      FILE* fopen(const char *path, const char* mode);
 *      FILE* fdopen(int fd, const char *mode);
 *      FILE* freopen(const char *path, cnst char *mode, FILE *stream);
 * 
 * The change implemented for the fopen keyworkd in C, refers to a mode, the letter
 * 'x', that appears as a solution to prevent trunk fills with 'w' or 'w+' mode. Think
 * of it as an append or modify mode.
 * 
 * Also, another change relates with 'fopen_s' that help to detect flaws in the
 * provided buffers.
*/

int main(int argc, char **argv)
{
    print("fopen in C11 allows append/modify mode, to prevent empty files!\n");
    return 0;
}
