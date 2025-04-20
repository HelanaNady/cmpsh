#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void interactive_mode() {
    printf("interactive mode");
}

void non_interactive_mode() {
    printf("non interactive mode");
}

bool is_interactive_mode(char* command) {
    int size = strlen(command);
    const char* lastThreeLetters = &command[size - 3];
    printf("%s\n", lastThreeLetters);

    if (strcmp(".sh", lastThreeLetters) == 0) {
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

int exit(void) {
    return 0;
}

int cd_command(char** arguments) {
    return 0;
}

int pwd_command(char** arguments) {

}

int overwrite_paths(char** arguments) {

}

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