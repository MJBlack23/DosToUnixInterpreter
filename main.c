#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// Local files
#include "src/io.h"
#include "src/strings.h"
#include "src/pipe.h"

#include "src/exec.h"

int main()
{
    // Print a welcome message for the user with basic instructions
    print_welcome();

    // create some global variables
    char *line = NULL;  // null pointer for getline to write stdin into
    size_t given_len = 0; // size of object in memory
    ssize_t line_len; // signed size of object in memory

    int prompt_fd[2]; // file descriptor for the pipe to pass data back and forth
    // open a pipe to get input from the exec process
    init_pipe(prompt_fd);


    // print the initial prompt
    print_prompt(prompt_fd);

    // while the user hasn't input a terminating command
    while ((line_len = getline(&line, &given_len, stdin)) != -1) {

        // extract command(s) from the line
        char *cmd_ptr = strtok(line, "&");

        // For each command delimited by an Ampersand
        while (cmd_ptr != NULL)
        {
            // strip whitespace at the begining and end
            right_trim(cmd_ptr);
            left_trim(cmd_ptr);
            
            // Create a NULL terminated command array
            char *command[] = {cmd_ptr, NULL};
            
            // Create a new pipe 
            int pipe_fd[2];
            init_pipe(pipe_fd);

            int status = run_command(command, pipe_fd);

            if (status > -1)
            {
                char read_buf[1];
                close(pipe_fd[1]);
                while (read(pipe_fd[0], read_buf, 1) > 0 && *read_buf != '\0')
                    putchar(*read_buf);
            }


            // temp printing stuff
            // printf("Command> |%s|\n", command);

            cmd_ptr = strtok(NULL, "&");
        }


        // print new prompt
        print_prompt(prompt_fd);
    }
    
    

    printf("\n");
    return 0;
}


// split on whitespace

// the first arg is the command
// see if it matches an accepted command
// if it does, check for
// redirects < or >
// pipes |
// switches (flags) .ie starting with -