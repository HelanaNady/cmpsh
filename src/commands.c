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

void execute_child_command(char** arguments) {
    // check first if command can be executed directly -> custom written script
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
    exit(EXIT_FAILURE);
}

char*** parse_pipe_commands(char** arguments, int processesNumber) {
    // allocate n string arrays
    char*** commandArguments = malloc(processesNumber * sizeof(char**));

    int index = 0;
    int current = 0;

    while (arguments[index] != NULL && current < processesNumber) {
        int start = index;
        int size = 0;

        while (arguments[index] != NULL && strcmp(arguments[index], "|") != 0) {
            index++;
            size++;
        }
        // allocaate for current command
        commandArguments[current] = malloc((size + 1) * sizeof(char*));

        for (int j = 0; j < size; j++) {
            commandArguments[current][j] = arguments[start + j];
        }

        commandArguments[current][size] = NULL;
        current++;

        if (arguments[index] != NULL) {
            index++;
        }

    }

    return commandArguments;
}

int execute_external_command(char** arguments) {
    pid_t waitPid;
    int status;

    int i = 0;
    int pipes = 0;

    while (arguments[i] != NULL) {
        if (strcmp(arguments[i], "|") == 0) {
            // printf("%d %s\n", i, arguments[i]);
            pipes++;
        }
        i++;
    }

    if (pipes == 0) {
        pid_t pid = fork();
        // child process
        if (pid == 0) {
            execute_child_command(arguments);
        }
        // parent
        else if (pid > 0) {
            waitPid = waitpid(pid, &status, WUNTRACED);
        }
    }
    // presence of one pipe is enough
    int processesNumber = pipes + 1;
    char*** commandArguments = parse_pipe_commands(arguments, processesNumber);

    // create n-1 pipes
    int fds[pipes][2];

    // pipe creations
    for (int j = 0; j < pipes; j++) {
        if (pipe(fds[j]) == -1) {
            perror("pipe failed");
            return 1;
        }
    }

    pid_t* pids = malloc(processesNumber * sizeof(pid_t));

    if (!pids) {
        fprintf(stderr, "An error has occured!\n");
    }

    // for in for loop
    for (int i = 0; i < processesNumber; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "An error has occured!\n");
        }

        if (pid == 0) {
            if (i == 0) {
                // change stdout to point to write of i only
                dup2(fds[i][1], STDOUT_FILENO);
            }
            else if (i == processesNumber - 1) {
                // change stdin to point to read of i-1 only
                dup2(fds[i - 1][0], STDIN_FILENO);
            }
            else {
                // change stdin to point to read of i-1
                // change stdout to point to write of i for next process
                dup2(fds[i - 1][0], STDIN_FILENO);
                dup2(fds[i][1], STDOUT_FILENO);
            }

            // close all of pipes fds 
            for (int j = 0; j < pipes; j++) {
                close(fds[j][0]);
                close(fds[j][1]);
            }

            // close(fds[i][0]);
            // close(fds[i][1]);

            execute_child_command(commandArguments[i]);
        }
        else {
            pids[i] = pid;
        }
    }

    // close all pipes
    for (int j = 0; j < pipes; j++) {
        close(fds[j][0]);
        close(fds[j][1]);
    }

    // wait for all children
    for (int k = 0; k < processesNumber; k++) {
        waitpid(pids[k], NULL, 0);
    }

    return 1;
}
