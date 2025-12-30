#include "shell.h"
/**
 * env_shell - prints the current environment variables
 * @av: argument vector
 * @envp: environment variables
 * Return: 0
 */
int env_shell(char **av, char **envp)
{
	int i = 0;

	if (strcmp(av[0], "env") == 0)
	{
		while (envp[i] != NULL)
		{
			printf("%s\n", envp[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
