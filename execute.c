#include "shell.h"

/**
 * shell_execute - execute a command
 * @av: argument vector
 * @prog_name: name of the shell (for error messages)
 * @envp: environment variables
 * @line_count: current line number
 */
void shell_execute(char **av, char *prog_name, char **envp, int line_count)
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(av[0], av, envp) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, av[0]);
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}
