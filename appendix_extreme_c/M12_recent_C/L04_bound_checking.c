// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * A buffer is a region of memory that is a middle step between process, in other words, is a
 * place holder. They have boundaries and if you surpass them an 'buffer overflow' happens which
 * can be used for exploitation or Denial Of Service (DOS).
 * 
 * The 'strcpy' and 'strcat' are among the most vulnerables from 'string.h'. But C11 came
 * with some boundary checking function, that are the ones with '_s' suffix. They accept
 * extra args that restricts certain operations.
 * 
 *      errno_t strcpy_s(char *restrict dest, rsieze_t destsz, constr char *restrict src);
 * 
 * Where 'dest' is destination, 'destsz' is the restriction and 'src' is the source to copy. 
*/

int main(int argc, char **argv)
{
    printf("If you want a secure code use: strcpy_s and strcat_s :D\n");
    return 0;
}
