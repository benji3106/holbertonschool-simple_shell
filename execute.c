#include "shell.h"

/**
 * trim_newline - remove trailing newline
 * @line: input line
 */
void trim_newline(char *line)
{
	size_t len;

	if (line == NULL)
		return;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/**
 * run_command - execute a command with arguments (no PATH for now)
 * @argv: NULL-terminated array (argv[0] is the command)
 * @prog: program name (argv[0] of the shell)
 * @envp: environment variables
 */
void run_command(char **argv, char *prog, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		return;
	}

	if (pid == 0)
	{
		execve(argv[0], argv, envp);
		fprintf(stderr, "%s: %s\n", prog, strerror(errno));
		_exit(127);
	}

	(void)waitpid(pid, &status, 0);
}
