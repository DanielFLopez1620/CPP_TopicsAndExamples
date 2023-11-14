// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc, and there is a possibility it doesn't work or lead to a crash

#include <stdio.h>

/**
 * A program is a process, which should come from an executable and it can be executed multiple times.
 * In Unix-like systems, the onion exposes some utilities with the API. But before moving on, there must
 * be a distinction between 'process creation' (spawning a new one) and 'process execution' (using an
 * existing one as host), which are create by syscalls. So, there are two keyworks 'fork' which spawns
 * process and 'exec' which replace the caller of a process.
 * 
 * Here, the POSIX is also important, the 'fork' function is found in the 'unistd.h' file, the 'posix_spawn'
 * and the 'posix_spawnp' are from the file 'spawn.h', and the group of exec*a re also in 'unistd.h'. Where
 * this last ones aren't sys calls, but rather functions to use them.
 *
 * The POSIX standard only expose the C standard library, but when you use a termina there are more complex
 * utilites, and it can be as simple as using 'ls'. After all, a process is just a call (syscall) that is 
 * recieved by the 'system call interface' which passes it down to the Kernel. Each task in monolithic
 * kernels is tracked, it is put in the queue of the 'task scheduler unit'
 * 
 * The processes have parents, if the kernel created them it is called 'init' and sometimes it becomes the 
 * parent of the orphan process. Also, note that the processes end up making a tree, which can be seen with
 * the command 'pstree' in the terminal.
 * 
 * PROCESS CREATION: For this we will need to use 'fork' function from the 'unistd.h' library. When called, 
 * it creates a copy of the caller process and then they start to run concurerntly, the child process
 * inherits the memory segment (and its content).
 * 
 * 
 * NOTE: In newer versions, the 'init' process has been replaced with 'systemd daemon' or 'systemd', to learn
 * about this change you can check here: https://www.tecmint.com/systemd-replaces-init-in-linux.
*/

#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("In the lesson, we introduce the process exectution, if you want more info, look at: \n");
    printf("\t- https://github.com/openunix/cygwin/blob/master/winsup/cygwin/fork.cc\n");
    printf("\t- http://man7.org/linux/man-pages/man2/fork.2.html\n");
    
    printf("\nExample: Creating a process:\n");
    printf("Parent ID: %d\n", getpid());
    __pid_t ret = fork();
    if(ret)
    {
        printf("Child ID: %d\n", ret);
    }
    else
    {
        printf("Child ID: %d\n", getpid());
    }
    printf("Type CTRL+C to continue, this was intented to see the process with 'pstree'...\n");
    while (1);
    return 0;
}
