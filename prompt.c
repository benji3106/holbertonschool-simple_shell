#include "shell.h"

/**
 * shell_prompt - display the shell prompt if in interactive mode
 * @interactive: whether the shell is in interactive mode
 *
 * Return: void
 */
void shell_prompt(int interactive)
{
	if (interactive)
		printf("($) ");
	fflush(stdout);
}
