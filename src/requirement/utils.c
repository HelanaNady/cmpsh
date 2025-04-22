#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

const int TOKENS_BUFFER_SIZE = 50;


void interactive_mode() {
    printf("interactive mode \n");

}

void non_interactive_mode(char* scriptName) {
    if (!is_non_interactive_mode(scriptName)) {
        return;
    }
    printf("non interactive mode \n");
}

bool is_non_interactive_mode(char* scriptName) {
    int size = strlen(scriptName);
    const char* last_three_letters = &scriptName[size - 3];

    if (strcmp(".sh", last_three_letters) == 0) {
        return true;
    }
    else {
        return false;
    }
}

void cmp_shell_loop() {
    // contains main loop of shell
    char* inputLine = NULL;
    char** arguments = NULL;
    // int commandStatus = -1;

    do {
        printf("%s", "cmpsh> ");
        inputLine = read_line();

        if (strcmp(inputLine, "\n") == 0) {
            printf("empty command \n");
            continue;
        }

        arguments = parse_line(inputLine);


        // check if it runs in interactive mode or non interactive mode
        // interactive_mode();

        // free resources after usage
        free(inputLine);
        free(arguments);
    }
    while (true);
}

char* read_line() {
    // read input line 
    size_t bufferSize = 0;
    char* inputLine = NULL;

    if (getline(&inputLine, &bufferSize, stdin) == -1) {
        perror("An error has occured!");
        exit(EXIT_FAILURE);
    }

    return inputLine;
}

char** parse_line(char* line) {
    int bufferSize = TOKENS_BUFFER_SIZE;
    char** tokens = malloc(sizeof(char*) * bufferSize);

    int index = 0;
    char* token;
    char* rest = line;

    if (!tokens) {
        perror("An error has occured!");
        exit(EXIT_FAILURE);
    }

    token = strtok_r(line, " ", &rest);
    
    while (token != NULL) {
        tokens[index] = token;
        index++;
        token = strtok_r(NULL, " ", &rest);
    }

    // marking end of array to get size later
    tokens[index] = NULL;
    return tokens;
}

// built in commands

int exit_command(void) {
    return 0;
}

int cd_command(char** arguments) {
    return 0;
}

int pwd_command(char** arguments) {
    return 0;
}

int overwrite_paths(char** arguments) {
    return 0;
}
