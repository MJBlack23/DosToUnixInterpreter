#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// Local files
#include "src/io.h"

int string_len(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }

    return len;
}

char *string_reverse(char *str)
{
    int len = string_len(str);
    int i, end = len - 1;
    char temp[len];
    char *new_str = malloc(len);

    for (i = 0; i < len; ++i)
    {
        temp[i] = str[end];
        --end;
    }
    
    // create a proper string with a null termination
    temp[i] = '\0';

    strcpy(new_str, temp);
    return new_str;
}

char *left_trim(char *str) {
    while (isspace((unsigned char) *str))
    {
        str++;
    }

    // strcpy(trimmed, str);

    return str;
}

char *right_trim(char *str) {
    char *reversed = string_reverse(str);

    char *right_trimmed = left_trim(reversed);

    return string_reverse(right_trimmed);
}


int main()
{
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

    // extracting a command
    // char *user_command = malloc(sizeof(char) * 0);



    // print the initial prompt
    print_prompt(pipe_fd);

    // while the user hasn't input a terminating command
    // "exit" | EOF | '\n'
    while ((line_len = getline(&line, &given_len, stdin)) != -1) {

        // extract command(s) from the line
        // int command_count = 1;
        // int *command_breaks = malloc(sizeof(int) * 0);
        char *cmd_ptr = strtok(line, "&");

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



// int last_break = 0;
//         for (int i = 0; i < line_len - 1; ++i) {
//             if (line[i] == '&' || line[i] == '\0' || line[i] == '\n') {
//                 // found a break, so create a command
//                 int cur_len = i - last_break - 1;
//                 user_command = realloc(user_command, sizeof(char) * cur_len);
//                 for (int j = 0; j <= cur_len; ++j) {
//                     user_command[j] = line[j + last_break];
//                 }

//                 last_break = i + 1;
//                 printf("Command: %s|\n", user_command);
//                 printf("last_break: %d", last_break);
//             }
//         }

//         if (line[line_len] == '\n' || line[line_len] == '\0') {
//             printf("found a spec char");
//         }

//         // echo the statement back to the user
//         printf("You said (%ld chars): ", line_len);
//         printf("%s\n", line);