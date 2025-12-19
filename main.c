#include "shell.h"

/**
 * main - simple UNIX command interpreter
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line;
	size_t len;
	ssize_t nread;
	int interactive;

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

		run_command(line, av[0]);
	}
}
