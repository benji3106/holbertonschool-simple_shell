#include "shell.h"

/**
 * execute_cmd - execute a command
 * @av: argument vector
 * @prog_name: name of the shell (for error messages)
 * @envp: environment variables
 */
void execute_cmd(char **av, char *prog_name, char **envp)
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
			perror(prog_name);
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}
