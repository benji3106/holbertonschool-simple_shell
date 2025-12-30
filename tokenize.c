#include "shell.h"

/**
 * shell_tokenize - split a line into tokens
 * @line: the line to split
 *
 * Return: array of tokens, or NULL on failure
 */
char **shell_tokenize(char *line)
{
	char **tokens;
	char *token;
	char *copy;
	int count = 0;
	int i = 0;

	copy = strdup(line);
	if (copy == NULL)
		return (NULL);

	token = strtok(copy, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	free(copy);

	tokens = malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;

	return (tokens);
}
