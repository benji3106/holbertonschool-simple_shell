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
 * run_command - execute a single-word command
 * @cmd: command string
 * @prog: program name (argv[0])
 */
void run_command(char *cmd, char *prog)
{
	pid_t pid;
	int status;
	char *argv_exec[2];

	argv_exec[0] = cmd;
	argv_exec[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		return;
	}

	if (pid == 0)
	{
		execve(cmd, argv_exec, environ);
		fprintf(stderr, "%s: %s\n", prog, strerror(errno));
		_exit(127);
	}

	(void)waitpid(pid, &status, 0);
}
