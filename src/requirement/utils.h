#ifndef UTILS_H
#define UTILS_H

void interactive_mode();
void non_interactive_mode();
bool is_interactive_mode(char* command);
void cmp_shell_loop(void);
char* read_line();
char** parse_line(char* line);

// built in commands
int exit_command(void);
int cd_command(char** arguments);
int pwd_command(char** arguments);
int overwrite_paths(char** arguments);

#endif 