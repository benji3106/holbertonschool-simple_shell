#include "shell.h"

/**
 * main - simple UNIX command interpreter
 * @ac: argument count
 * @av: argument vector
 * @envp: environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **envp)
{
	char *line;
	size_t len;
	ssize_t nread;
	int interactive;
	char **argv_cmd;

	(void)ac;
	line = NULL;
	len = 0;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		trim_newline(line);

		if (line[0] == '\0')
			continue;

		argv_cmd = tokenize(line);
		if (argv_cmd == NULL || argv_cmd[0] == NULL)
		{
			free(argv_cmd);
			continue;
		}

		run_command(argv_cmd, av[0], envp);
		free(argv_cmd);
	}
}
