#include <libgen.h>
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>

void print_prompt() {
    char cwd[PATH_MAX];

    // try to get the cwd, if the call fails print a fallback prompt
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("ttsh - getcwd");
        printf("> ");
        fflush(stdout);
        return;
    }

    // print only the last directory
    printf("%s> ", basename(cwd));
    fflush(stdout);
}