#include "shell.h"

/**
 * main - simple shell
 * @argc: argument count (unused)
 * @argv: argument vector
 * @envp: environment variables
 *
 * Return: 0
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n;
	int interactive;
	char *av[2];

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("$ ");
		fflush(stdout);

		n = getline(&line, &len, stdin);
		if (n == -1)
		{
			printf("\n");
			free(line);
			exit(0);
		}

		line[n - 1] = '\0';
		if (line[0] == '\0')
			continue;

		av[0] = line;
		av[1] = NULL;
		execute_cmd(av, argv[0], envp);
	}

	return (0);
}
