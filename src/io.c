#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "colors.h"
#include "io.h"


void print_welcome()
{
    clear_screen();
    printf("|================================================================================================|\n");
    printf(" Welcome to the DOS to UNIX command interpreter.\n");
    printf("  Created by Matt Black\n");
    printf("  CIS-570 Spring 2019\n");
    printf("  Usage:\n");
    printf("    > Enter a DOS command and it will be executed as a unix style command on your system.\n\n\n");
}

void print_prompt()
{
    char *args[] = {"pwd"};
    int status = run_command(args);
    
    if (status > -1)
        printf(" %s$%s ", KCYN, KNRM);
}

void clear_screen() {
    char *args[] = {"clear", NULL};
    run_command(args);
}

int run_command(char *args[])
{
    char *command = args[0];
    pid_t pid = fork();
    int status;

    switch(pid) {
        case -1:
            perror("Failed to fork a command");
            perror(command);
            exit(1);
        case 0:
            
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