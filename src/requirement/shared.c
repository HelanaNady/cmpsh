#include "shared.h"

const int BUFFER_SIZE = 1024;

struct Builtin {
    char* commandName;
    int (*commandFunction)(char**);
};