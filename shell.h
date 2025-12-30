#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void execute_cmd(char **av, char *prog_name, char **envp);
char **tokenize(char *line);
int exit_shell(char **av, char *line);
#endif
