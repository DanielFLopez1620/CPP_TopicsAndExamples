// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * There would be cases where the memory is a scarce and valuable resource, sometimes it 
 * can be called 'constrained environment' which means there are constrains related to the
 * resources, in this case memory, so the solution is to search optimization and good
 * management.
 * 
 * One example of this cases are embedded systems, where memory and time are the matter,
 * also called 'time complexity', which is added by every algorithm (Big-O functions). The
 * key is to get the best of both worlds (memory and time). So, it is a good practice to
 * assume we are working with constrained environments.
 * 
 * - PACKED STRUCTURES: They discard memory aligment and a better storing (compact). It
 * consumes less memory, but create a slower program.
 * 
 * - COMPRESSION: Good for programs with a lot of text data, because it has a high
 * compression ratio, which allows to save memory but has a CPU intensive cost.
 * 
 * - EXTERNAL DATA STORAGE: It means taking help for the network, cloud or a hard drive,
 * it relates with the cache (it is not main storage), although external memory is lows,
 * it can be balanced with algorithms, some services are PostgreSQL and Oracle.
 * 
 * - PERFORMANT ENVIRONMENT: Another problem is that for faster algorithms, you will need
 * more memory. One option can be 'caching' data which can increase performance, if it is 
 * the correct implementation. In simple terms, it refers to the interaction between two
 * data storage that read/write speeds are different, and the CPU is fast but fetching data
 * from memory is slow. So, you need to study the 'performance gain', this implies that the 
 * cache usually is the faster (and commonly the smaller) memory, then you can exchange data
 * from the two drives to the faster when needed, this is known as 'hit' (already in cache)
 * and 'miss' (pending in cache).
 * 
 *    - Cache-friendly code: It needs to consider the CPU and the fetching process, and in 
 *      the process, blocks are transferred into the cache (usually more that needed). A
 *      proximity is a value needed near the previous address (of the block) added, the reason
 *      follows the 'principle of locality' (neighborhood) and this can be exploted to create 
 *      more efficient algorithms.
*/

#include <stdlib.h> // For allocation functions in heap
#include <string.h> // For string functions like strcmp

int main(int argc, char **argv)
{
    //-->195
    return 0;
}
