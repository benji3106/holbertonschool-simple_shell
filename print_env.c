#include "shell.h"

/**
 * print_env - print current environment
 * @envp: environment variables
 */
void print_env(char **envp)
{
	int i;

	if (envp == NULL)
		return;

	for (i = 0; envp[i] != NULL; i++)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
