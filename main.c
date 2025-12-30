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
	int line_count = 0;

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		shell_prompt(interactive);
		n = getline(&line, &len, stdin);
		if (n == -1)
		{
			if (interactive)
				printf("\n");
			free(line);
			exit(0);
		}

		line_count++;
		line[n - 1] = '\0';
		shell_process_line(line, argv, envp, line_count);
	}

	return (0);
}
