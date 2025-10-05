#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "commands.h"
#include "shared.h"

const int BUFFER_SIZE = 1024;

#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

const struct Builtin builtins[] = {
    {"cd", cd_command},
    {"pwd", pwd_command},
    {"exit", exit_command},
    {"path", overwrite_paths}
};

#define BUILTIN_SIZE (sizeof(builtins) / sizeof(builtins[0]))

void interactive_mode() {
    printf("interactive mode \n");
}

void non_interactive_mode(char* scriptName) {
    readScript(scriptName);
}

void execute_command(char** arguments) {
    char* command = arguments[0];
    bool isBuiltinCommand = false;

    for (int i = 0; i < BUILTIN_SIZE; i++) {
        if (strcmp(command, builtins[i].commandName) == 0) {
            builtins[i].commandFunction(arguments);
            isBuiltinCommand = true;
        }
    }

    if (!isBuiltinCommand) {
        execute_external_command(arguments);
    }
}

void cmp_shell_loop() {
    // contains main loop of shell
    char* inputLine = NULL;
    char** arguments = NULL;
    // int commandStatus = -1;

    do {
        printf(CYAN "%s", "cmpsh> ");
        printf(RESET);
        inputLine = read_line();

        if (strcmp(inputLine, "\n") == 0) {
            printf("empty command \n");
            continue;
        }

        arguments = parse_line(inputLine);
        // char* command = arguments[0];

        execute_command(arguments);

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

    if (!tokens) {
        perror("An error has occured!");
        exit(EXIT_FAILURE);
    }

    int size = strlen(line);
    int tokenCount = 0;
    int index = 0;

    while (index < size) {

        while (index < size && line[index] == ' ') {
            index++;
        }
        if (index >= size) {
            break;
        }

        int start = index;
        int end = index;
        char* token = NULL;

        if (line[index] == '"' || line[index] == '\'') {
            char quote = line[index];
            index++;
            start = index;

            while (index < size && line[index] != quote) {
                index++;
            }

            end = index - 1;
            index++;
        }
        else if (line[index] == '|' || line[index] == '<' || line[index] == '>') {
            token = malloc(2);
            token[0] = line[index];
            token[1] = '\0';
            index++;

            tokens[tokenCount] = token;
            tokenCount++;

            continue;
        }
        else {
            while (index < size && line[index] != ' ' &&
                line[index] != '|'
                && line[index] != '<'
                && line[index] != '>') {
                index++;
            }

            end = index - 1;
        }

        int tokenSize = end - start + 1;
        token = malloc(tokenSize + 1);
        token = strncpy(token, line + start, tokenSize);

        token[tokenSize] = '\0';
        tokens[tokenCount] = token;
        tokenCount++;
    }

    tokens[tokenCount] = NULL;
    return tokens;
}

/// file handler stuff

bool canOpenFile(FILE* fptr) {
    if (fptr == NULL) {
        fprintf(stderr, "File does not exist");
        return false;
    }
    return true;
}

void readScript(const char* filename) {
    // open file in read mode
    FILE* fptr = fopen(filename, "r");

    if (!canOpenFile(fptr)) {
        return;
    }

    char buffer[BUFFER_SIZE];

    // fgets prints line by line
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        // get size of buffer
        int i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
            }
            i++;
        }

        char** arguments = parse_line(buffer);
        execute_command(arguments);
    }

    fclose(fptr);
}

// char** parse_script_line(char* buffer) {
//     // if /n replace with null 
//     // else do nothing 
// }