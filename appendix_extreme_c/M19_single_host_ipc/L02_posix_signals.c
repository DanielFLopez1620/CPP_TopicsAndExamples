// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Threads and processes can use signals (which are a notification for events or errors), for example,
 * when a reboot is going to happen a SIGTERM is sent to all processes.
 * 
 * Some of the most common signals are SIGINT, SIGTERM and SIGKILL, but there are more, each process has 
 * a standard and an action, and can relate with aborts, alarms, errors, interrupts, and more...
 * You can learn more about them in the next link: http://www.man7.org/linux/man-pages/man7/signal.7.html
 * 
 * For testing signals, you can use the command 'kill' with the respective signal and process ID:
 *      
 *      kill -<signal> <pid>
 * 
 * Now, let's experiment with the code:
 * 
 *      gcc L02_posix_signals.c -o  ps.out
 *      ./ps.out &   # This will return a <pid>
 *
 * Then you can try different signals:
 *      
 *      kill -SIGUSR2 <pid>
 *      kill -SIGUSR1 <pid>
 *      kill -SIGINT <pid>
 *      kill -SIGKILL <pid>
 * 
 * NOTE: Whenever you press "CTRL + C" in a terminal running a process, you are actually sending
 * SIGINT signals to the process running, if it isn't enough for killing the program it can be rised
 * to use kill signal.s
 * 
*/

#include <stdlib.h>
#include <signal.h>

void handler_usignal(int signal);
void handler_sigint(int signal);
void handler_sigkill(int signal);

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, handler_usignal);
    signal(SIGUSR2, handler_usignal);
    signal(SIGINT, handler_sigint);
    signal(SIGKILL, handler_sigkill);

    while(1);

    return 0;
}


void handler_usignal(int signal)
{
    switch (signal )
    {
    case SIGUSR1:
        printf("SIGUSR1 activated!\n");
        break;
    case SIGUSR2:
        printf("SIGUSR2 activated!\n");
    default:
        printf("Unknown sigal received\n");
        break;
    }
}

void handler_sigint(int signal)
{
    printf("Keyboard Interrupt signal was received");
}

void handler_sigkill(int signal)
{
    printf("The program ist being killed, write you another time!\n");
    exit(0);
}