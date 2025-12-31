#include "shell.h"

/**
 * process_line - parse and execute a line
 * @line: input line
 * @argv0: shell name
 * @envp: environment
 * @line_no: current line number
 * @interactive: 1 if interactive mode
 * @last_status: pointer to last status
 */
static void process_line(char *line, char *argv0, char **envp,
		unsigned int line_no, int interactive, int *last_status)
{
	char **av;
	char *fullpath;

	if (line[0] == '\0')
		return;

	av = tokenize(line);
	if (av == NULL || av[0] == NULL)
	{
		free(av);
		return;
	}

	fullpath = resolve_path(av[0], envp);
	if (fullpath == NULL)
	{
		fprintf(stderr, "%s: %u: %s: not found\n", argv0, line_no, av[0]);
		*last_status = 127;
		free(av);
		if (!interactive)
			exit(*last_status);
		return;
	}

	av[0] = fullpath;
	execute_cmd(av, argv0, envp);
	*last_status = 0;

	free(fullpath);
	free(av);
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
	char *line;
	size_t len;
	ssize_t n;
	int interactive;
	unsigned int line_no;
	int last_status;

	(void)argc;
	line = NULL;
	len = 0;
	line_no = 0;
	last_status = 0;
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

		process_line(line, argv[0], envp, line_no, interactive, &last_status);
	}
}
