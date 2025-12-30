#include "shell.h"

/**
 * print_prompt - display prompt if interactive
 * @interactive: 1 if stdin is terminal
 */
void print_prompt(int interactive)
{
	if (interactive)
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
}
