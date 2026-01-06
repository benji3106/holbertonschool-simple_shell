#include "shell.h"

/**
 * handle_exit - exit the shell
 * @av: tokenized command
 * @linep: pointer to input line
 */
void handle_exit(char **av, char **linep)
{
	free(av);
	free(*linep);
	exit(0);
}
