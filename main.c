#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "src/io.h"



int main() {
    print_welcome();
    
    print_prompt();
    return 0;
}
