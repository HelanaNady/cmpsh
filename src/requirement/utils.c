#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "builtin.h"
#include "shared.h"

const int BUFFER_SIZE = 1024;

const struct Builtin builtins[] = {
    {"cd", cd_command},
    {"pwd", pwd_command},
    {"exit", exit_command},
    {"paths", overwrite_paths}
};

#define BUILTIN_SIZE (sizeof(builtins) / sizeof(builtins[0]))

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
        char* command = arguments[0];

        // int i = 0;

        // while(command[i] != '\0') {
        //     printf("%d - %c \n", i, command[i]);
        //     i++;
        // }

 
        for (int i = 0; i < BUILTIN_SIZE; i++) {
            if(strcmp(command, builtins[i].commandName) == 0) {
                printf("command name: %s \n", command);
                builtins[i].commandFunction(arguments);
            }
        }

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

    size_t length = strlen(inputLine);
    if (length > 0 && inputLine[length - 1] == '\n') {
        inputLine[length - 1] = '\0';
    }

    return inputLine;
}

char** parse_line(char* line) {
    int bufferSize = BUFFER_SIZE;
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

