// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code wasn't tested

// NOTE: Do not try to run this file as it is experimental and may change you config.
// RISK OF SYS CORRUPTION

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>

// This is not part of POSIX!
#include <sys/syscall.h>

int main(int argc, char** argv) 
{
    char str[20] = "Kam";
    char message[64] = "";

    // Call the hello world system call
    int ret_val = syscall(999, str, 4, message, 64);
    if (ret_val < 0) 
    {
        printf("[ERR] Ret val: %d\n", ret_val);
        return 1;
    }
    printf("Message: %s\n", message);
    return 0;
}