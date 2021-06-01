/*
* COURSE: COMP 3340 SECTION [A02]
* INSTRUCTOR: Rasit Eskicioglu
* NAME: Adedotun Adeyemo
* ASSIGNMENT: 2
* QUESTION: 1
*/
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>

char str[80];                  // buffer
int fd[2];                     // file descriptor
char cat[3] = {'c', 'a', 't'}; // array to store characters of cat
char dog[3] = {'d', 'o', 'g'}; // array to store characters of cat
int n;
bool running = true;

void signalHandler1(int signum); // prototype of signalHandler1
void signalHandler2(int signum); // prototype of signalHandler2
void signalHandler3(int signum); // prototype of signalHandler3

// Helper function that replaces a set of 3 characters with another set of 3 characters
void replace(char a[], char b[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (tolower(str[i]) == a[0] && tolower(str[i + 1]) == a[1] && tolower(str[i + 2]) == a[2])
        {
            str[i] = b[0];
            str[i + 1] = b[1];
            str[i + 2] = b[2];
        }
    }
}

// Helper method that clears the buffer
void clear()
{
    for (int i = 0; i < 80; i++)
    {
        str[i] = '\0';
    }
}

// helper method that calls reads input calls other helper methods clear() and replace() and writes to pipe
void helper(char a[], char b[], bool change)
{
    do
    {
        // clear the buffer
        clear();
        // read from the pipe
        n = read(fd[0], str, 80);
        // if the boolean change is true replace the characters of array a in the buffer with the carracter of array b
        if (change)
        {
            replace(a, b);
        }
        write(1, str, n);
    } while (n != 0);
    // if read gets an EOF then exit program
    if (n <= 0 || n == EOF)
    {
        exit(0);
    }
}

// Signal handler 1, is invoked when a SIGUSR1 is sent to the process and replaces dog with cat
void signalHandler1(int signum)
{
    signal(signum, signalHandler1);
    helper(dog, cat, true);
}

// Signal handler 2, is invoked when a SIGUSR2 is sent to the process and replaces cat with dog
void signalHandler2(int signum)
{
    signal(signum, signalHandler2);
    helper(cat, dog, true);
}

// Signal handler 3, is invoked when a SIGALRM is sent to the process and does not do any replacemnts
void signalHandler3(int signum)
{
    helper(cat, dog, false);
    signal(signum, signalHandler3);
}

int main(int argc, char **argv)
{
    // if the pipe fails close the program and mention there is an error
    if (pipe(fd) < 0)
    {
        exit(1);
    }
    int pid = fork();

    // if the fork fails close the program and mention there is an error
    if (pid < 0)
    {
        exit(1);
    }
    // if we are in the parent process
    else if (pid > 0)
    {
        // Registering Signal handlers
        signal(SIGUSR1, signalHandler1);
        signal(SIGUSR2, signalHandler2);
        signal(SIGALRM, signalHandler3);
        // run the default action i.e. replcae cat with dog
        helper(cat, dog, true);
        // if read gets an EOF then exit program
        if (n <= 0 || n == EOF)
        {
            return 0;
        }
    }
    // if we are in the child process
    else
    {
        dup2(fd[1], 1);
        execvp(argv[1], argv + sizeof(char));
    }
    argc += 0;
    return 0;
}
