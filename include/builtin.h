#ifndef TTSH_BUILTIN_H
#define TTSH_BUILTIN_H

typedef int (*builtin_func)(int argc, char **argv);
typedef void (*help_func)(void);

int is_builtin(char *name);
int run_builtin(int argc, char **argv);

int builtin_help(int argc, char **argv);
void builtin_help_help();

int builtin_exit(int argc, char **argv);
void builtin_exit_help();

int builtin_cd(int argc, char **argv);
void builtin_cd_help();

int builtin_pwd(int argc, char **argv);
void builtin_pwd_help();

#endif