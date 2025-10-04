#ifndef SHARED_H
#define SHARED_H

struct Builtin {
    const char* commandName;
    int (*commandFunction)(char**);
};

extern const int BUFFER_SIZE;
extern const struct Builtin builtins[];

extern char** shell_paths;  
extern int shell_path_count;

#endif