// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * They are needed as one process cannot have all the resources, and they would be needed somewhere
 * else. For making this possible, you need to put it in a 'place' is available for other, or you
 * sent the state to share it. So we can generate a classification in two types, 'pull-based' techniques
 * (require a medium of storage) and the 'push-based' (related to a channel or transmission).
 * 
 * For now, we will cover the ones related with pull-based, we can mention the next ones:
 * 
 * - SHARED MEMORY: A region that is shared (and available) to some process, which is a space in
 *   memory. And remember, it is temporary.
 * - FILESYSTEM: Save and use, it is the oldest one, but it can lead to difficulties in the 
 *  synchronization for the access.
 * - NETWORK SERVICES: Once it is connected,, it can be used to store and retrieve shared states.
*/

int main(int argc, char **argv)
{
    
    return 0;
}
