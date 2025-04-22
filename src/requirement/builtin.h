#ifndef BUILT_IN_H
#define BUILT_IN_H

void interactive_mode();
void non_interactive_mode(char* scriptName);
bool is_non_interactive_mode(char* scriptName);

// shell specific
void cmp_shell_loop();
char* read_line();
char** parse_line(char* line);

// built in commands
int exit_command(void);
int cd_command(char** arguments);
int pwd_command(char** arguments);
int overwrite_paths(char** arguments);

#endif 