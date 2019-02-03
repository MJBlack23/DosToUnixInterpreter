#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

// Local files
#include "src/io.h"

// temp
#include <unistd.h>

#define NEW_LINE '\n';




// void get_commands(char *input) {
//     char *pch;
//     pch = strtok(input, "&");

//     while (pch != NULL)
//     {
//         int count = 0;
//         for (int i = 0; i < strlen(pch); i += 1)
//         {
//             if (pch[i] != ' ')
//             {
//                 pch[count += 1] = pch[i];
//             }
//         }
//         pch[count] = '\0';
//         printf("%s\n", pch);
//         pch = strtok(NULL, "&");
//     }
// }

int main() {
    print_welcome();

    // create some global variables
    char *line = NULL;  // null pointer for getline to write stdin into
    size_t given_len = 0; // size of object in memory
    ssize_t line_len; // signed size of object in memory

    int pipe_fd[2]; // file descriptor for the pipe to pass data back and forth

    // open a pipe to get input from the exec process
    if (pipe(pipe_fd) == -1) {
        perror("Failed to open a pipe.");
        exit(1);
    }

    // print the initial prompt
    print_prompt(pipe_fd);

    // while the user hasn't input a terminating command
    // "exit" | EOF | '\n'
    while ((line_len = getline(&line, &given_len, stdin)) != -1) {


        // echo the statement back to the user
        printf("You said: ");
        printf("%s\n", line);

        // print new prompt
        print_prompt(pipe_fd);
    }
    
    

    printf("\n");
    return 0;
}


// TODO: get CWD from forked execv and pipe it back to the prompt, print it in front of the $ prompt

// garbage
// printf("%s\n", input);

// once an input is received...

// remove any new lines

// aplit on ampersands

// for each 'command'

// split on whitespace

// the first arg is the command
// see if it matches an accepted command
// if it does, check for
// redirects < or >
// pipes |
// switches (flags) .ie starting with -

// get_commands(input);
// split into words...
// char *pch;
// pch = strtok(input, "&");

// while (pch != NULL) {
//     printf("%s\n", pch);
//     pch = strtok(NULL, "&");
// }

// static char input[512];

// while (input != "exit")