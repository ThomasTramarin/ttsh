#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int run_external(int argc, char **argv) {
    if (argc == 0)
        return 0;

    pid_t pid = fork();

    if (pid < 0) {
        perror("ttsh - fork failed");
        return 1;
    }

    if (pid == 0) {
        argv[argc] = NULL;
        execvp(argv[0], argv);
        perror("ttsh - exec failed");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return 1;
    }
}