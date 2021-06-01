/*
* COURSE: COMP 3340 SECTION [A02]
* INSTRUCTOR: Rasit Eskicioglu
* NAME: Adedotun Adeyemo
* ASSIGNMENT: 2
* QUESTION: 2
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler 1, is invoked when a SIGUSR1 is sent to the process
void signalHandler1(int signum)
{
    signal(signum, signalHandler1);
    printf("Running Signal Handler 1\n");
    sleep(3);
}

// Signal handler 2, is invoked when a SIGUSR2 is sent to the process
void signalHandler2(int signum)
{
    signal(signum, signalHandler2);
    printf("Running Signal Handler 2\n");
    sleep(2);
}

int main()
{
    int pid = fork();

    // if the fork fails close the program and mention there is an error
    if (pid < 0)
    {
        exit(1);
    }
    // if we are in the parent process
    else if (pid > 0)
    {
        // sleep so that the signals handlers can be registered before sending signals
        sleep(3);
        kill(pid, SIGUSR1);
        kill(pid, SIGUSR1);
        // sleep so that the previous signals handlers can be resolved before sending new signals
        sleep(2);
        kill(pid, SIGUSR2);
        kill(pid, SIGUSR1);
        // sleep so the last signal handler can finish before code stops
        sleep(3);
    }
    // if we are in the child process
    else
    {
        // Registering Signal handlers
        signal(SIGUSR1, signalHandler1);
        signal(SIGUSR2, signalHandler2);
        // sleep so the signals can be handled while parent process tries to send more signals
        sleep(10);
    }

    return 0;
}
