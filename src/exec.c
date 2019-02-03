#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "exec.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int run_command(char *args[], int pipe_fd[])
{
    char *command = args[0];
    pid_t pid = fork();
    int status;

    switch (pid)
    {
    case -1:
        perror("Failed to fork a command");
        perror(command);
        exit(1);
    case 0:
        // Redirect the stdout to the input of the pipe
        dup2(pipe_fd[1], STDOUT); // make stdout go to pipe
        close(pipe_fd[0]);              // close the read end of pipe
        close(pipe_fd[1]);              // close the *old* write end of the pipe
        execvp(command, args);
    }

    if (waitpid(pid, &status, 0) == -1)
    {
        return -1;
    }
    else
    {
        return status;
    }
}