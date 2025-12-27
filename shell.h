#ifndef SHELL_H
#define SHELL_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void execute_cmd(char **av, char *prog_name, char **envp);

#endif
