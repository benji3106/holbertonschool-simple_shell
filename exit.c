#include "shell.h"

/**
 * shell_exit - free resources and exit the shell
 * @av: argument vector
 * @line: input line
 *
 * Return: exit the program
 */
int shell_exit(char **av, char *line)
{
	if (strcmp(av[0], "exit") == 0)
	{
		free(av);
		free(line);
		exit(0);
	}
	return (0);
}
