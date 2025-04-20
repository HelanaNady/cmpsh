#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

const int TOKENS_BUFFER_SIZE = 50;


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
    char* inputLine = NULL;
    char** arguments = NULL;
    int commandStatus = -1;

    do {
        printf("%s", "cmpsh> ");
        inputLine = read_line();
        arguments = parse_line(inputLine);

        // printf("%s\n", inputLine);

        // check if it runs in interactive mode or non interactive mode
        // if (is_interactive_mode(command)) {
        //     interactive_mode();
        // }
        // else {
        //     non_interactive_mode();
        // }

        // free resources after usage
        free(inputLine);
        free(arguments);
    }
    while (true);
}

char* read_line() {
    // read input line 
    int bufferSize = 0;
    char* inputLine = NULL;

    if (getline(&inputLine, &bufferSize, stdin) == -1) {
        perror("An error has occured!");
        exit(EXIT_FAILURE);
    }

    return inputLine;
}

char** parse_line(char* line) {
    // tokenize input line 

    int bufferSize = TOKENS_BUFFER_SIZE;
    char** tokens = malloc(sizeof(char*) * bufferSize);
    
    int index = 0;
    char* token;
    char* rest;

    if (!tokens) {
        perror("An error has occured!");
        exit(EXIT_FAILURE);
    }

    token = strtok_r(line, " ", &rest);

    while (token != NULL) {
        // printf("%s\n", token);
        token = strtok_r(NULL, " ", &rest);
        tokens[index] = token;
        index++;
    }

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

}

int overwrite_paths(char** arguments) {

}
