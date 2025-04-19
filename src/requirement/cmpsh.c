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

bool isInteractiveMode (char* command) {
    int size = strlen(command);
    const char* lastThreeLetters = &command[size - 3];
    printf("%s\n", lastThreeLetters);

    if(strcmp(".sh", command) == 0) {
        return true;
    }
    else {
        return false;
    }
}

int main (int argc, char** argv) {
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