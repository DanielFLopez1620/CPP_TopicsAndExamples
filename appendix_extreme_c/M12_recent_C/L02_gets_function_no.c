// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * GETS FUNCTION WAS REMOVED:
 * It was due to overflow attacks, now you should use fgets.
 * 
 * NOTE: Gets cannot know the lenght of the incoming line, which can be an inconvinient.
 * 
*/

int main(int argc, char const *argv[])
{
    printf("Do not use 'gets' function, you get exposed to overflow attacks!\n");
    return 0;
}


