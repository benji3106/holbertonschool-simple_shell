#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>


extern char **environ;


#define PROMPT "#shellobscur$ "


void print_prompt(int interactive);
void trim_newline(char *line);
void run_command(char *cmd, char *prog);

#endif
