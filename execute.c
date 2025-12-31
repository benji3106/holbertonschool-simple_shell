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
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return;
	}

	if (pid == 0)
	{
		execve(av[0], av, envp);
		perror(prog_name);
		_exit(127);
	}

	(void)waitpid(pid, &status, 0);
}
