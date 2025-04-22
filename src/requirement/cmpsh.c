#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

int main(int argc, char** argv) {
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