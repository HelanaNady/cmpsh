#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

int main(int argc, char** argv) {
    // command?
    char* command = argv[1];
    printf("%s\n", argv[1]);
    // check if it runs in interactive mode or non interactive mode
    if (is_interactive_mode(command)) {
        interactive_mode();
    }
    else {
        non_interactive_mode();
    }
    return 0;
}