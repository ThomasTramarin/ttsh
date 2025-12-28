#ifndef TTSH_PARSER_H
#define TTSH_PARSER_H

char *read_line();
int parse_line(char *line, char **args);

#endif