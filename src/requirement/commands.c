#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sched.h>

#include "commands.h"
#include "shared.h"
#include <bits/waitflags.h>
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
    for(int i = 0; i < shell_path_count; i++) {
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

    for(int i = 0; i < shell_path_count; i++) {
        shell_paths[i] = arguments[i+1];
        printf("%s\n", shell_paths[i]);
    }

    return 0;
}

int execute_external_command(char** arguments) {
    pid_t pid, waitPid;
    int status;

    pid = fork();
    
    // child process
    if (pid == 0) {
        char command[PATH_MAX];
        snprintf(command, sizeof(command), "/%s", arguments[0]);

        // search each path 
        for (int i = 0; i < shell_path_count; i++) {
            // char* path = strcat(shell_paths[i], command);
            char fullPath[PATH_MAX];
            snprintf(fullPath, sizeof(fullPath), "%s%s", shell_paths[i], command);
            
            if (access(fullPath, X_OK) == 0) {
                printf("%s\n", fullPath);
                execv(fullPath, arguments);
            }
        }
    }
    // parent
    else if (pid > 0) {
        // wait on return signal
        do {
            waitPid = waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));

        // check exit status of child process
        int exit_status = WEXITSTATUS(status);

        if(exit_status != 0) {
            perror("An error has occured!");
        }
    }

    return 0;
}
