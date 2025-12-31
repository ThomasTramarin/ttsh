#include "builtin.h"
#include "external.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *line;
    int last_status = 0;

    while ((line = read_line()) != NULL) {
        char *args[128];
        int argc;

        argc = parse_line(line, args);

        // if the input is an empty string
        if (argc == 0) {
            free(line);
            continue;
        }

        // check if the command is a shell built-in
        if (is_builtin(args[0])) {
            int res = run_builtin(argc, args);

            if (res == -1) {
                fprintf(stderr, "ttsh - command not found: %s\n", args[0]);
                last_status = 127; // command not found status code
            } else if (res < -1) {
                last_status = -2 - res; // in this case status_code represents the status the shell
                break;                  // process will return
            } else {
                last_status = res;
            }
        } else {

            last_status = run_external(argc, args);
        }

        free(line);
    }

    return last_status;
}
