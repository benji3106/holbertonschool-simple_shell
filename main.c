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
	char *line;
	size_t len;
	ssize_t n;
	int interactive;
	char **av;
	char *fullpath;

	(void)argc;
	line = NULL;
	len = 0;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);

		n = getline(&line, &len, stdin);
		if (n == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}

		if (n > 0 && line[n - 1] == '\n')
			line[n - 1] = '\0';

		if (line[0] == '\0')
			continue;

		av = tokenize(line);
		if (av == NULL || av[0] == NULL)
		{
			free(av);
			continue;
		}

		fullpath = resolve_path(av[0], envp);
		if (fullpath == NULL)
		{
			fprintf(stderr, "%s: %s: not found\n", argv[0], av[0]);
			free(av);
			continue;
		}

		av[0] = fullpath;
		execute_cmd(av, argv[0], envp);

		free(fullpath);
		free(av);
	}

	free(line);
	return (0);
}
