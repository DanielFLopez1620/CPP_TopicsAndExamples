// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <string.h> // For implementing char arrays or "words"
#include <stdio.h>

/**
 * STACK: It is mandatory for process execution (unlike the Heap), because it manages
 * the functions and its calls. The allocation is fast and the dellocations/management 
 * is automatic, but you should not overestimate it and trust in excess.
 * 
 * The perfect example of this is running the current file... So, give it a try...
 * 
 * Most likely, it will happen something like:
 * 
 * *** stack smashing detected ***
*/


int main(int argc, char** argv)
{
    printf("This program may crash....\n");
    printf("Do not forget to read the lesson.");

    char str[10];
    strcpy(str, "something_very_large_like_this_str_write_by_me");

    return 0;
}