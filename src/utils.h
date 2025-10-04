#ifndef UTILS_H
#define UTILS_H

void interactive_mode();
void non_interactive_mode(char* scriptName);

// shell specific
void cmp_shell_loop();
char* read_line();
char** parse_line(char* line);

void readScript(const char* filename);

#endif 