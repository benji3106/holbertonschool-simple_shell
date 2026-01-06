#include "shell.h"
/**
 * handle_exit - handle the exit command
 * @av: argument vector
 * @linep: pointer to the input line
 */
void handle_exit(char **av, char **linep)
{
    free(av);
    free(*linep);
    exit(0);
}
