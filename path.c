#include "shell.h"

/**
 * build_candidate - build "dir/cmd"
 * @dir: directory
 * @cmd: command
 *
 * Return: malloc'ed candidate or NULL
 */
static char *build_candidate(const char *dir, const char *cmd)
{
	size_t dlen, clen;
	char *full;

	dlen = strlen(dir);
	clen = strlen(cmd);

	full = malloc(dlen + 1 + clen + 1);
	if (full == NULL)
		return (NULL);

	memcpy(full, dir, dlen);
	full[dlen] = '/';
	memcpy(full + dlen + 1, cmd, clen);
	full[dlen + 1 + clen] = '\0';

	return (full);
}

/**
 * str_dup - duplicate a string using malloc
 * @s: input string
 *
 * Return: malloc'ed copy or NULL
 */
static char *str_dup(const char *s)
{
	size_t len;
	char *copy;

	len = strlen(s);
	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);

	memcpy(copy, s, len + 1);
	return (copy);
}

/**
 * resolve_path - resolve cmd using PATH (or direct path if contains '/')
 * @cmd: command
 * @envp: environment
 *
 * Return: malloc'ed full path if found, NULL otherwise
 */
char *resolve_path(const char *cmd, char **envp)
{
	const char *path;
	char *path_copy, *dir, *candidate;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (str_dup(cmd));
		return (NULL);
	}

	path = get_env_value("PATH", envp);
	if (path == NULL || path[0] == '\0')
		return (NULL);

	path_copy = str_dup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		candidate = build_candidate(dir, cmd);
		if (candidate == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		if (access(candidate, X_OK) == 0)
		{
			free(path_copy);
			return (candidate);
		}

		free(candidate);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
