#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void shell_execute(char **av, char *prog_name, char **envp, int line_count);
char **shell_tokenize(char *line);
int shell_exit(char **av, char *line);
int shell_env(char **av, char **envp);

#endif
