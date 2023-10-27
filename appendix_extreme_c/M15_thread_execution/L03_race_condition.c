// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Let's try an experiment with threads and see what happens when the order is unknown.
 * 
 * You can compile and run with:
 *      
 *      gcc L03_race_condition.c -o rc.out -lpthread
 *      ./rc.out
 * 
 * Try to run it multiple times, the order of the players can change, but the messages are complete and not
 * fragmented, so 'printf' is thread safe.
 * 
*/

#include <stdlib.h>

#include <pthread.h>

void* thread_content(void *arg);

int main(int argc, char **argv)
{
    pthread_t th_message1;
    pthread_t th_message2;
    pthread_t th_message3;

    printf("This code may generate a mess as an output...\n Let's check\n");

    int res1 = pthread_create(&th_message1, NULL, thread_content, "Player1_Ready");
    int res2 = pthread_create(&th_message2, NULL, thread_content, "Player2_Ready");
    int res3 = pthread_create(&th_message3, NULL, thread_content, "Player3_Ready");

    if(res1 || res2 || res3)
    {
        printf("ERROR!  Threads cannot be created....\n");
        exit(1);
    }

    res1 = pthread_join(th_message1, NULL);
    res2 = pthread_join(th_message2, NULL);
    res3 = pthread_join(th_message3, NULL);

    if(res1 || res2 || res3)
    {
        printf("ERROR!  THreads cannot be joined....\n");
        exit(2);
    }

    return 0;
}

/**
 * Generic content for a thread to print a message
 * 
 * @param arg Generic param, maybe a string? You know, because it sends messages?
*/
void* thread_content(void *arg)
{
    char* str = (char*) arg;
    printf("Content received: %s\n", str);
    return NULL;
}