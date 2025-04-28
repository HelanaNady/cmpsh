#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sched.h>
#include <sys/stat.h>
#include <bits/waitflags.h>


#include "commands.h"
#include "shared.h"
#include <sys/wait.h>


#define PATH_MAX 1024

char** shell_paths = NULL;
int shell_path_count = 0;

void init_shell_paths() {
    shell_path_count = 1;
    shell_paths = malloc(shell_path_count * sizeof(char*));
    shell_paths[0] = strdup("/bin");
}

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
    // reset everything
    for (int i = 0; i < shell_path_count; i++) {
        free(shell_paths[i]);
    }

    free(shell_paths);
    shell_path_count = 0;

    int i = 1;
    while (arguments[i] != NULL) {
        shell_path_count++;
        i++;
    }

    shell_paths = malloc(shell_path_count * sizeof(char*));

    for (int i = 0; i < shell_path_count; i++) {
        char* new_path = arguments[i + 1];

        if (strcmp(new_path, ".") == 0) {
            // add current directory path 
            char buffer[PATH_MAX];
            new_path = getcwd(buffer, PATH_MAX);
        }

        // check if it is a valid directory path
        struct stat buffer;
        if (stat(shell_paths[i], &buffer) < -1) {
            continue;
        }

        shell_paths[i] = new_path;
    }

    return 0;
}

bool is_executable(char* path) {
    return access(path, X_OK) == 0;
}

int execute_external_command(char** arguments) {
    pid_t pid, waitPid;
    int status;

    pid = fork();

    // child process
    if (pid == 0) {
        // check first if command can be executed directly - custom script
        if (strncmp(arguments[0], "./", 2) == 0) {
            char buffer[PATH_MAX];
            getcwd(buffer, sizeof(buffer));

            char fullPath[PATH_MAX];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", buffer, arguments[0] + 2);

            execv(arguments[0], arguments);
            fprintf(stderr, "An error has occured!\n");
        }
        
        char command[PATH_MAX];
        snprintf(command, sizeof(command), "/%s", arguments[0]);

        // search each path 
        for (int i = 0; i < shell_path_count; i++) {
            char fullPath[PATH_MAX];

            snprintf(fullPath, sizeof(fullPath), "%s%s", shell_paths[i], command);

            if (is_executable(fullPath)) {
                execv(fullPath, arguments);
                fprintf(stderr, "An error has occured! not valid \n");
            }
        }
        fprintf(stderr, "An error has occured! not found also\n");
    }
    // parent
    else if (pid > 0) {
        waitPid = waitpid(pid, &status, WUNTRACED);
    }
    return 1;
}
