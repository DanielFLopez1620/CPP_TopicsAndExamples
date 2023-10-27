// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * To make a code thread safe you will need that the pointers passed aren't 'dangling pointers' (which means that they
 * point to an adress where no variable is allocated). Now, let's fix the previous race condition. Check the code below:
 * 
 *      gcc L04_fix_race_condition.c -o fix_rc.out -lpthread
 *      ./fix_rc.out
 * 
 * Keep in mind that if you need to be able to detect the dangling pointers, you will need a 'memory profiler'. We will
 * check it with 'valgrind'. If is better to check, so you can prevent crash or logical errorers (that are not common, but
 * possible). You can try with:
 * 
 *      gcc -g L04_fix_race_condition.c -o fix_rc.out -lpthread
 *      valgrind ./fix_rc.out
*/

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* thread_content(void* arg);

int main(int argc, char const *argv[])
{
    printf("This code does not have a race conditon problem...\n");
    
    pthread_t th_message1;
    pthread_t th_message2;
    pthread_t th_message3;

    char message1[8], message2[8], message3[8];

    // Creation of the strings, so they are allocated.
    strcpy(message1, "Player1");
    strcpy(message2, "Player2");
    strcpy(message3, "Player3");

    int res1 = pthread_create(&th_message1, NULL, thread_content, message1);
    int res2 = pthread_create(&th_message2, NULL, thread_content, message2);
    int res3 = pthread_create(&th_message3, NULL, thread_content, message3);

    if (res1 || res2 || res3)
    {
        printf("ERROR.... The thread could not be created...\n");
        exit(1);
    }

    res1 = pthread_detach(th_message1);
    res2 = pthread_detach(th_message2);
    res3 = pthread_detach(th_message3);

    if (res1 || res2 || res3)
    {
        printf("ERROR.... The thread could not be joined...\n");
        exit(1);
    }
    
    // Final deallocation
    pthread_exit(NULL);

    return 0;
}

void* thread_content(void* arg)
{
    char* str = (char*)arg;
    printf("Message received: %s\n", str);
    return NULL;
}
