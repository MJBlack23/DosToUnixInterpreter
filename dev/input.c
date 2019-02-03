#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "exec.h"


void parse_command()
{
    char *input = "ls -la";
    // given a command parse out it's arguements and run the command
    char *pch;
    pch = strtok(input, " ,.-");

    while (pch != NULL)
    {
        printf("%s\n", pch);
        pch = strtok(NULL, " ,.-");
    }
}

int main() {
    
    parse_command();
}