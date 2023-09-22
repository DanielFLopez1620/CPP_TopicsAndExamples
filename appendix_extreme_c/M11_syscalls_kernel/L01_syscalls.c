// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Remember the spearation between user and kernel spaces, here is a limit that the user cannot traspass, 
 * in other words, it meansthat no process of the user space can access the hardware, kernel and related. 
 * 
 * This purpose is achieved by the syscalls, for example, when using a file with 'fread', it is a libc
 * implementation with the correponding syscalls to achieve the task. So the process then is passed to the
 * kernel.
 * 
 * Keep in mind that there is only one kernel performing the logic of the syscalls, so if the call is busy
 * the user has to wait. The responses here can be divided in two: blocking and non-blocking. Another aspect
 * here is that the arguments are copied from and to the user space, so it means, the kernel can manage pointers
 * and variables (short variables). Finally, we can say that the kernel has full access to all the resources in 
 * the system, so a user need permission to do some syscalls.
 * 
 * Now, we can make syscalls with C by using the <sys/syscall.h> with the command 'syscall', as this is 
 * a exposed tool that can be used when some calls are not implemented. Each syscall has its own unique 
 * specific system call number in Linux.
 * 
 * Do not forget to compile this code and use 'strace' with it to check the sys calls.
 * 
*/

// Definition required to use parts of the GNU C Library (glibc)
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char **argv)
{
    char message[34] = "This is a different hello world!\n";

    // Implementation of a syscall
    // For writing, 3 args are needed: 1 is stdout, message is the buffer and 33 is the length
    syscall(__NR_write, 1, message, 33);
    return 0;
}
