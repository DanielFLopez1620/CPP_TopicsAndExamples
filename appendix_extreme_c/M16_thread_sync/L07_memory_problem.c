// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * 
*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int* shared_resource;

void* first_thread_content(void* arg);
void* second_thread_content(void* arg);

//--> 

void* first_thread_content(void* arg)
{
    int local_num = 1620;
    shared_resource = &local_num;
    usleep(10);
    return NULL;
}

void* second_thread_content(void* arg)
{
    printf("Num: %d\n", *shared_resource);
    return NULL;
}