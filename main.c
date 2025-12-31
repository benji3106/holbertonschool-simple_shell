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
	unsigned int line_no = 0;
	int last_status = 0;

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
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(last_status);
		}

		line_no++;

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
			fprintf(stderr, "%s: %u: %s: not found\n",
				argv[0], line_no, av[0]);
			last_status = 127;
			free(av);

			/* if non-interactive, stop immediately like sh */
			if (!interactive)
			{
				free(line);
				exit(last_status);
			}

			continue;
		}

		av[0] = fullpath;
		execute_cmd(av, argv[0], envp);
		last_status = 0; /* (optionnel) mieux: récupérer le vrai status */

		free(fullpath);
		free(av);
	}
}
