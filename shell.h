#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "#shellobscur$ "
#define MAX_ARGS 64

void print_prompt(int interactive);
void trim_newline(char *line);



void run_command(char **argv, char *prog, char **envp);

#endif

