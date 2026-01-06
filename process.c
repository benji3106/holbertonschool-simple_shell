#include "shell.h"

/**
 * shell_process_line - process a single line of input
 * @line: the input line to process
 * @argv: argument vector from main
 * @envp: environment variables
 * @line_count: current line number
 *
 * Return: void
 */
void shell_process_line(char *line, char **argv, char **envp, int line_count)
{
	char **av;

	if (line[0] == '\0')
		return;

	av = shell_tokenize(line);
	if (av == NULL || av[0] == NULL)
	{
		free(av);
		return;
	}

	shell_exit(av, line);

	if (shell_env(av, envp))
	{
		free(av);
		return;
	}

	shell_execute(av, argv[0], envp, line_count);
	free(av);
}
