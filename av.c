#include <stdio.h>  /* printf */

/**
 * main - affiche tous les arguments sans utiliser ac
 * @ac: nombre d'arguments (non utilisé)
 * @av: tableau de strings contenant les arguments
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	int i;

	/*
	 * (void)ac empêche le warning "unused parameter"
	 * On dit au compilateur : "oui je sais, je ne l'utilise pas exprès"
	 */
	(void)ac;

	i = 0;

	/*
	 * STRUCTURE DE av :
	 * -----------------
	 * Quand tu lances : ./prog hello world
	 *
	 * av[0] = "./prog"    (nom du programme)
	 * av[1] = "hello"
	 * av[2] = "world"
	 * av[3] = NULL        (toujours NULL à la fin)
	 *
	 * C'est pour ça qu'on peut faire while(av[i]) :
	 * NULL = 0 = faux, donc la boucle s'arrête
	 */
	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}

	return (0);
}
