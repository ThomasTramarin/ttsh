#ifndef TTSH_BUILTIN_H
#define TTSH_BUILTIN_H

typedef int (*builtin_func)(int argc, char **argv);

int is_builtin(char *name);
int run_builtin(int argc, char **argv);

int builtin_exit(int argc, char **argv);

#endif