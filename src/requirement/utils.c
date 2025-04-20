#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

void interactive_mode() {
    printf("interactive mode");
}

void non_interactive_mode() {
    printf("non interactive mode");
}

bool is_interactive_mode(char* command) {
    int size = strlen(command);
    const char* last_three_letters = &command[size - 3];
    printf("%s\n", last_three_letters);

    if (strcmp(".sh", last_three_letters)) {
        return true;
    }
    else {
        return false;
    }
}

void cmp_shell_loop(void) {
    // contains main loop of shell
}

char* read_line() {
    // read input line 
}


char** parse_line(char* line) {
    // tokenize input line 
}

// built in commands

int exit_command(void) {
    return 0;
}

int cd_command(char** arguments) {
    return 0;
}

int pwd_command(char** arguments) {

}

int overwrite_paths(char** arguments) {

}
