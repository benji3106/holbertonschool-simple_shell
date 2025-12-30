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
	char **av;

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
			if (interactive)
				printf("\n");
			free(line);
			exit(0);
		}

		line[n - 1] = '\0';
		if (line[0] == '\0')
			continue;

		av = tokenize(line);
		if (av == NULL || av[0] == NULL)
		{
			free(av);
			continue;
		}
		
		exit_shell(av, line);
		execute_cmd(av, argv[0], envp);
		free(av);
	}

	return (0);
}
