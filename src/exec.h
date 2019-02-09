#ifndef EXEC_H
#define EXEC_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int run_command(char *args[], int pipe_fd[]);

#endif