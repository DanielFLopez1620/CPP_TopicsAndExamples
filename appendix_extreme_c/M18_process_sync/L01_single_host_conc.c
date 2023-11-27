// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include<stdio.h>

/**
 * Threads are linked to the life of a process, but process can live longer in any OS, although you need
 * to secure them in order to sync and use them concurrent.
 *
 * In this cases, accessing to shared resources at the same time can be a problem. So, there are
 * some mechanism:
 * 
 * - NAMED POSIX SEMPAHORES: POSIX semaphores like the ones in threads, but with names.
 * - NAMED MUTEXES: Mutex with custom name.
 * - NAMED CONDITION VARIABLES: You got the idea 'name' + 'condition'.
 * 
 * In the next codes, we will check this issue. 
*/

int main(int argc, char **argv)
{
    printf("Before moving on, do not forget to check about semaphores, mutex and conditions.\n");
    printf("In the next codes, we will check a new approach of them but in the cases of processes.\n");
    return 0;
}
