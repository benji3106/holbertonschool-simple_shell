#include "shell.h"

/**
 * execute_cmd - execute a command
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

	/* Vérifier si terminaison normale (équivalent de WIFEXITED) */
	if ((status & 0x7F) == 0)
	{
		/* Extraire le code de sortie (équivalent de WEXITSTATUS) */
		return (status >> 8);
	}

	/* Terminé par signal = échec */
	return (1);
}
