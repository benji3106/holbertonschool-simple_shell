#include "shell.h"

/**
 * shell_execute - execute a command
 * @av: argument vector
 * @prog_name: name of the shell (for error messages)
 * @envp: environment variables
 * Return: exit status of the command
 */
int execute_cmd(char **av, char *prog_name, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return (1);
	}

	if (pid == 0)
	{
		execve(av[0], av, envp);
		perror(prog_name);
		_exit(127);
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	return (1);
}
