#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printWelcome();

int main() {
    printWelcome();
    return 0;
}

void printWelcome() {
    printf("|================================================================================================|\n");
    printf(" Welcome to the DOS to UNIX command interpreter.\n");
    printf("  Created by Matt Black\n");
    printf("  CIS-570 Spring 2019\n");
    printf("  Usage:\n");
    printf("    > Enter a DOS command and it will be executed as a unix style command on your system.\n\n\n");

    char *cmd = "pwd";
    char *argv[2];
    argv[0] = "pwd";
    argv[1] = NULL;

    // pid_t pid;

    if (fork() == 0) {
        execvp(cmd, argv);
        printf(" > ");
    }
}