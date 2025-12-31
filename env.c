#include "shell.h"

/**
 * get_env_value - get env var value from envp
 * @name: variable name (ex: "PATH")
 * @envp: environment
 *
 * Return: pointer to value, or NULL if not found
 */
const char *get_env_value(const char *name, char **envp)
{
	size_t nlen;
	int i;

	if (name == NULL || envp == NULL)
		return (NULL);

	nlen = strlen(name);

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], name, nlen) == 0 && envp[i][nlen] == '=')
			return (envp[i] + nlen + 1);
	}
	return (NULL);
}
