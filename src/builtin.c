#include "builtin.h"
#include <stdlib.h>
#include <string.h>

struct builtin_entry {
    const char *name;
    builtin_func func;
};

static struct builtin_entry builtins[] = {
    {"exit", builtin_exit}, // TODO: implement a help message for each builtin
};

static const int BUILTIN_COUNT = sizeof(builtins) / sizeof(builtins[0]);

int is_builtin(char *name) {
    if (!name)
        return 0;

    for (int i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(name, builtins[i].name) == 0)
            return 1;
    }

    return 0;
}

/**
 * Returns:
 *  [>=0] -> status code
 *  [=-1] -> command not found
 *  [<=-2] -> special code to stop the shell, used in `exit`
 *            the exit code of the ttsh process will be `-2 -(n)`
 */
int run_builtin(int argc, char **argv) {
    if (argc == 0)
        return 0;

    for (int i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(argv[0], builtins[i].name) == 0) {
            return builtins[i].func(argc, argv);
        }
    }

    return -1; // -1 if the function was not found
}

int builtin_exit(int argc, char **argv) {
    int status = 0;
    if (argc > 1)
        status = atoi(argv[1]); // TODO: check if the input is a valid number

    return -2 - status;
}
