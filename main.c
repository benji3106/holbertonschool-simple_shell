#include "shell.h"

/**
 * process_line - parse and execute a line
 * @line: input line (modified)
 * @argv0: program name (argv[0])
 * @envp: environment variables
 * @line_no: current line number
 * @interactive: 1 if interactive mode, 0 otherwise
 *
 * Return: 0 on success/continue, 127 if command not found in non-interactive
 */
static int process_line(char *line, char *argv0, char **envp,
		unsigned int line_no, int interactive)
{
	char **av;
	char *fullpath;

	if (line[0] == '\0')
		return (0);

	av = tokenize(line);
	if (av == NULL || av[0] == NULL)
	{
		free(av);
		return (0);
	}

	if (strcmp(av[0], "env") == 0)
	{
		print_env(envp);
		free(av);
		return (0);
	}

	fullpath = resolve_path(av[0], envp);
	if (fullpath == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n", argv0, line_no, av[0]);
		free(av);
		return (interactive ? 0 : 127);
	}

	av[0] = fullpath;
	execute_cmd(av, argv0, envp);

	free(fullpath);
	free(av);
	return (0);
}


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
	unsigned int line_no = 0;
	int last_status = 0;

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		print_prompt(interactive);

		n = getline(&line, &len, stdin);
		if (n == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_no++;

		if (n > 0 && line[n - 1] == '\n')
			line[n - 1] = '\0';

		last_status = process_line(line, argv[0], envp, line_no, interactive);
		if (!interactive && last_status != 0)
			break;
	}

	free(line);
	return (last_status);
}
