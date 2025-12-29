#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct builtin_entry {
    const char *name;  // command name
    builtin_func code; // code for the command
    help_func help;    // help function (void function which prints the help message for the command)
};

// ========== BUILTIN TABLE ==========
static struct builtin_entry builtins[] = {
    {"help", builtin_help, builtin_help_help},
    {"exit", builtin_exit, builtin_exit_help},
};

#define BUILTIN_COUNT (sizeof(builtins) / sizeof(builtins[0]))

// ========== CHECK BUILTIN ===========
int is_builtin(char *name) {
    if (!name)
        return 0;

    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(name, builtins[i].name) == 0)
            return 1;
    }

    return 0;
}

// ========== EXECUTE BUILTIN ==========

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

    for (size_t i = 0; i < BUILTIN_COUNT; i++) {
        if (strcmp(argv[0], builtins[i].name) == 0) {

            return builtins[i].code(argc, argv);
        }
    }

    return -1; // -1 if the function was not found
}

// ========== HELP BUILTIN ==========
int builtin_help(int argc, char **argv) {
    if (argc == 1) { // only help
        printf("Available builtins:\n");
        for (size_t i = 0; i < BUILTIN_COUNT; i++) {
            printf("    %s\n", builtins[i].name);
        }
        return 0;
    } else if (argc == 2) { // help <cmd>
        for (size_t i = 0; i < BUILTIN_COUNT; i++) {
            if (strcmp(argv[1], builtins[i].name) == 0) {
                builtins[i].help();
                return 0;
            }
        }

        // command not found
        fprintf(stderr, "ttsh - no help for '%s'\n", argv[1]);
        return 1;
    }

    // too many args
    fprintf(stderr, "ttsh - usage: help [command]\n");
    return 1;
}

void builtin_help_help() {
    printf(
        "help [command]\n"
        "Display list of built-in commands or help for a specific command.\n");
}

// ========== EXIT BUILTIN ==========
int builtin_exit(int argc, char **argv) {
    int status = 0;
    if (argc > 1)
        status = atoi(argv[1]); // TODO: check if the input is a valid number

    return -2 - status;
}

void builtin_exit_help() {
    printf(
        "exit [status]\n"
        "Exit the shell.\n"
        "If status is provided, the shell exits with that code.\n"
        "EXAMPLES:\n"
        "   exit\n"
        "   exit 2\n");
}
