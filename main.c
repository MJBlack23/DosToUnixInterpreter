#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Local files
#include "src/io.h"
#include "src/strings.h"


int main()
{
    // Print a welcome message for the user with basic instructions
    print_welcome();

    // create some global variables
    char *line = NULL;  // null pointer for getline to write stdin into
    size_t given_len = 0; // size of object in memory
    ssize_t line_len; // signed size of object in memory

    int pipe_fd[2]; // file descriptor for the pipe to pass data back and forth
    // open a pipe to get input from the exec process
    if (pipe(pipe_fd) == -1)
    {
        perror("Failed to open a pipe.");
        exit(1);
    }



    // print the initial prompt
    print_prompt(pipe_fd);

    // while the user hasn't input a terminating command
    while ((line_len = getline(&line, &given_len, stdin)) != -1) {

        // extract command(s) from the line
        char *cmd_ptr = strtok(line, "&");

        // For each command delimited by an Ampersand
        while (cmd_ptr != NULL)
        {
            // strip whitespace at the begining and end
            char *command = right_trim(left_trim(cmd_ptr));

            // temp printing stuff
            printf("Command> |%s|\n", command);

            cmd_ptr = strtok(NULL, "&");
        }


        // print new prompt
        print_prompt(pipe_fd);
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