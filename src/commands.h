#ifndef COMMANDS_H
#define COMMANDS_H

void init_shell_paths();

// built in commands
int exit_command(char** arguments);
int cd_command(char** arguments);
int pwd_command(char** arguments);
int overwrite_paths(char** arguments);

// external commands
int execute_external_command(char** arguments);
bool is_executable(char* path);
void execute_child_command(char** arguments);

// for pipeline commands
char*** parse_pipe_commands(char** arguments, int processesNumber);

#endif 