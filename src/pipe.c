#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void init_pipe(int p[2])
{
    if (pipe(p) == -1)
    {
        perror("Failed to open a pipe.");
        exit(1);
    }
}