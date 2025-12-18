#include <stdio.h>   /* printf, getline, fflush, stdin */
#include <stdlib.h>  /* free */
#include <unistd.h>

/**
 * main - affiche un prompt, lit une ligne, l'affiche
 *
 * Return: 0 en cas de succès, 1 sinon
 */
int main(void)
{
	char *line = NULL;  /* pointeur qui va recevoir la ligne lue */
	size_t len = 0;     /* taille du buffer (getline la gère) */
	ssize_t n;          /* nombre de caractères lus */

	/*
	 * ÉTAPE 1 : AFFICHER LE PROMPT
	 * ----------------------------
	 * printf sans \n → le texte reste dans le buffer
	 * fflush force l'affichage immédiat
	 */
	printf("$ ");
	fflush(stdout);

	/*
	 * ÉTAPE 2 : LIRE UNE LIGNE
	 * ------------------------
	 * getline(&line, &len, stdin)
	 *
	 * &line  : adresse du pointeur (getline va malloc pour nous)
	 * &len   : adresse de la taille (getline la met à jour)
	 * stdin  : lire depuis le clavier
	 *
	 * Retourne :
	 *   - nombre de caractères lus (incluant \n)
	 *   - -1 si EOF (Ctrl+D) ou erreur
	 */
	n = getline(&line, &len, stdin);

	/*
	 * ÉTAPE 3 : GÉRER EOF / ERREUR
	 * ----------------------------
	 * Si l'utilisateur fait Ctrl+D → n = -1
	 */
	if (n == -1)
	{
		free(line);  /* getline peut avoir malloc même si erreur */
		return (1);
	}

	/*
	 * ÉTAPE 4 : AFFICHER LA LIGNE
	 * ---------------------------
	 * line contient déjà le \n tapé par l'utilisateur
	 * donc pas besoin de printf("%s\n", line)
	 */
	printf("%s", line);

	/*
	 * ÉTAPE 5 : LIBÉRER LA MÉMOIRE
	 * ----------------------------
	 * getline a fait malloc → on doit faire free
	 */
	free(line);

	return (0);
}
