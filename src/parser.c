#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *read_line() {
    char *line = NULL;
    size_t len = 0;

    print_prompt();

    // read a line from the stdin
    ssize_t nread = getline(&line, &len, stdin);

    if (nread == -1) {
        free(line);
        return NULL;
    }

    // replace the new line character with the null term
    if (line[nread - 1] == '\n') {
        line[nread - 1] = '\0';
    }

    return line;
}

int parse_line(char *line, char **args) {
    char *token;
    int count = 0;

    token = strtok(line, " \t");
    while (token != NULL) {
        args[count++] = token;
        token = strtok(NULL, " \t");
    }
    args[count] = NULL;

    return count;
}