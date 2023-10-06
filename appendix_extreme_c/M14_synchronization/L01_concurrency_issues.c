// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Exist the probability that concurrency fails or its enough, even fixing them create problems, as adding
 * code make it different to its original root. Another problem is the 'data race' as the shared
 * resources  and need to improve mangament there.  And as you modify some task may not get the chance
 * to run and become 'starved'.
 * 
 * We call these problems:
 *  - INTRINSIC CONCURRENCY ISSUES: Due to lack of control mechanism.
 *    It is based on the concept that always a interleaving can happen, and it becomes and issue when some 
 *    constraints are not kept. This will lead to 'race condition' systems which means that the constraints
 *    can be missed at some point. 
 *    The real problem here is that it can generate data corruptions and vulnerate the 'data integrity'.
 *  - Post Synscorization issues: Attempt of resolution from the previous one.
*/

int main(int argc, char* *argv[])
{
    // Pseudo code for crash generation with interleaving in C
    printf("P1: Watch the pseudo code here to understand a little about interleavings...\ns");
    /**
     * Concurrent System 
     * {
     *  Shared State 
     *  {
     *      char *ptr = NULL; 
     *  }
     * 
     *  Task A
     *  {
     *      ptr = (char*) malloc(12 * sizeof(char));
     *      strcpy(ptr, "Trying!");
     *      printf("%s\n", ptr);
     *  }
     * 
     *  Task B
     *  {
     *      free(ptr);
     *      ptr = NULL;
     *  }
     * }
    */
    printf("<PSEUDOCODE>\n");
    printf("The problem is that the pointer can crash if it is freed when its value is NULL or before \
    the assign\n\n");
    // M
    return 0;
}
