#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "builtin.h"
#include "shared.h"

#define PATH_MAX 1024

int exit_command(char** arguments) {
    exit(EXIT_SUCCESS);
}

// cd directory
int cd_command(char** arguments) {
    char* directory = arguments[1];

    if (arguments[1] == NULL || chdir(directory) != 0) {
        perror("An error has occured!");
        return 1;
    }
    else {
        return 0;
    }
}

int pwd_command(char** arguments) {
    (void)arguments;

    char buffer[PATH_MAX];
    char* workingDirectory = NULL;

    workingDirectory = getcwd(buffer, PATH_MAX);

    if (workingDirectory == NULL) {
        perror("An error has occured!");
        return 1;
    }
    else {
        printf("%s\n", workingDirectory);
        return 0;
    }
}

int overwrite_paths(char** arguments) {
    return 0;
}
