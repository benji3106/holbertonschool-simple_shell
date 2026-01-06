#include "shell.h"
/**
 * handle_exit - handle the exit command
 * @av: argument vector
 * @linep: pointer to the input line
 * @status: exit status
 */
void handle_exit(char **av, char **linep, int status)
{
    free(av);
    free(*linep);
    exit(status);
}
