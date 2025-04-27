#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "commands.h"

// const int TOKENS_BUFFER_SIZE = 50;

int main(int argc, char** argv) {

    init_shell_paths();
    
    switch (argc) {
    case 1:
        cmp_shell_loop();
        break;

    case 2:
        char* scriptName = argv[1];
        non_interactive_mode(scriptName);
        break;

    default:
        exit(EXIT_SUCCESS);
        // return 0;
    }

    return 0;
}