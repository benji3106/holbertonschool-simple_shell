#include <stdio.h>
#include <unistd.h>

/**
 * main - démontre execve
 *
 * Return: 0 si succès, 1 si erreur
 */
int main(void)
{
	/*
	 * ÉTAPE 1 : CRÉER LE TABLEAU D'ARGUMENTS
	 * --------------------------------------
	 * C'est ce que ft_split_to_av fait pour toi
	 * 
	 * av[0] = "ls"   → nom du programme
	 * av[1] = NULL   → fin du tableau
	 */
	char *av[] = {"ls", NULL};

	printf("Avant execve\n");

	/*
	 * ÉTAPE 2 : EXECVE
	 * ----------------
	 * execve(chemin, arguments, environnement)
	 *
	 * "/bin/ls" = chemin complet vers le programme ls
	 * av        = les arguments {"ls", NULL}
	 * NULL      = pas d'environnement (ATTENTION ! voir plus bas)
	 *
	 * Si execve réussit :
	 *   - Ce programme DISPARAÎT de la mémoire
	 *   - Il est REMPLACÉ par /bin/ls
	 *   - Les lignes après n'existent plus
	 *
	 * Si execve échoue :
	 *   - Retourne -1
	 *   - Le programme continue normalement
	 */
	execve("/bin/ls", av, NULL);

	/*
	 * ÉTAPE 3 : GESTION D'ERREUR
	 * --------------------------
	 * On arrive ici SEULEMENT si execve a échoué
	 * 
	 * Raisons possibles :
	 *   - Le fichier n'existe pas
	 *   - Pas les permissions
	 *   - Ce n'est pas un exécutable
	 */
	printf("Erreur : execve a échoué !\n");

	return (1);
}
