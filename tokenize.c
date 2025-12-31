#include "shell.h"

/**
 * tokenize - split a line into tokens
 * @line: the line to split (modified by strtok)
 *
 * Return: array of tokens, or NULL on failure
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token;
	int i;

	tokens = malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (tokens == NULL)
		return (NULL);

	i = 0;
	token = strtok(line, " \t");
	while (token != NULL && i < MAX_ARGS)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t");
	}
	tokens[i] = NULL;

	return (tokens);
}
