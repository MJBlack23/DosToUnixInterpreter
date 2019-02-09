#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "colors.h"
#include "io.h"
#include "exec.h"


void print_welcome()
{
    printf("|================================================================================================|\n");
    printf(" Welcome to the DOS to UNIX command interpreter.\n");
    printf("  Created by Matt Black\n");
    printf("  CIS-570 Spring 2019\n");
    printf("  Usage:\n");
    printf("> Enter a DOS command and it will be executed as a unix style command on your system.\n\n\n");
}

int print_prompt(int pipe_fd[2])
{
    char *args[] = {"pwd", NULL};
    int status = run_command(args, pipe_fd);
    
    
    if (status > -1)
    {
        // read the results from the pipe into a character array
        char read_buf[1];
        // read the pipe into a readable buffer, and then output the content
        // don't output the null character or a new line
        while((read(pipe_fd[0], read_buf, 1)) > 0 && *read_buf != '\0' && *read_buf != '\n')
            putchar(*read_buf);

        // while the current character isn't a new line or NULL character
        // output the character
        printf(" %s>%s ", KCYN, KNRM);
        return 1;
    }

    return 0;
}

void clear_screen()
{
    char *clear[] = {"clear", NULL};
    execvp(clear[0], clear);
}
