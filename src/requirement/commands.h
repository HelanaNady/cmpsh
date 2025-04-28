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

#endif 