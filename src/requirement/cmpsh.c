#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void interactiveMode() {
    printf("interactive mode");
}

void nonInteractiveMode() {
    printf("non interactive mode");
}

bool isInteractiveMode(char* command) {
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

void shellLoop(void) {
    // contains main loop of shell
}

char* readLine() {
    // read input line 
}


char** parseLine(char* line) {
    // tokenize input line 
}

// built in commands

int exit(void) {
    return 0;
}

int cdCommand(char** arguments) {
    return 0;
}

int pwdCommand(char** arguments) {

}

int overwritePaths(char** arguments) {

}

int main(int argc, char** argv) {
    // command?
    char* command = argv[1];
    printf("%s\n", argv[1]);
    // check if it runs in interactive mode or non interactive mode
    if (isInteractiveMode(command)) {
        interactiveMode();
    }
    else {
        nonInteractiveMode();
    }
    return 0;
}