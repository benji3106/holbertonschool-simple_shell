#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define PROMPT "shellobscur "
#define MAX_ARGS 64

void print_prompt(int interactive);
void execute_cmd(char **av, char *prog_name, char **envp);
char **tokenize(char *line);

const char *get_env_value(const char *name, char **envp);
char *resolve_path(const char *cmd, char **envp);
void print_env(char **envp);

#endif
