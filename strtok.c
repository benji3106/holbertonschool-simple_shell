#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * is_separator - vérifie si le caractère est un séparateur
 * @c: le caractère à tester
 *
 * Return: 1 si c'est un séparateur, 0 sinon
 */
static int is_separator(char c)
{
	/*
	 * On teste si c est un séparateur
	 * Si oui, on retourne 1
	 * Si non, on retourne 0
	 */

	/* Est-ce un espace ? */
	if (c == ' ')
		return (1);

	/* Est-ce une tabulation ? */
	if (c == '\t')
		return (1);

	/* Est-ce un retour à la ligne ? */
	if (c == '\n')
		return (1);

	/* Ce n'est aucun des trois, donc pas un séparateur */
	return (0);
}

/**
 * count_words - compte le nombre de mots dans une chaîne
 * @str: la chaîne à analyser
 *
 * Return: nombre de mots
 */
static int count_words(char *str)
{
	int count;
	int in_word;

	/*
	 * count = combien de mots on a trouvés
	 * in_word = est-ce qu'on est actuellement dans un mot ?
	 *           0 = non, on est dans des espaces
	 *           1 = oui, on est dans un mot
	 */
	count = 0;
	in_word = 0;

	/*
	 * while (*str)
	 * 
	 * *str = le caractère actuel
	 * Si *str == '\0' (fin de chaîne), la boucle s'arrête
	 * Sinon on continue
	 */
	while (*str)
	{
		/*
		 * CONDITION 1 : On entre dans un nouveau mot ?
		 *
		 * !is_separator(*str) = ce n'est PAS un séparateur (c'est une lettre)
		 * !in_word = on n'était PAS dans un mot
		 *
		 * Si les deux sont vrais → on vient de trouver le DÉBUT d'un mot
		 */
		if (!is_separator(*str) && !in_word)
		{
			in_word = 1;  /* maintenant on est dans un mot */
			count++;      /* on a trouvé un nouveau mot */
		}
		/*
		 * CONDITION 2 : On sort d'un mot ?
		 *
		 * is_separator(*str) = c'est un séparateur (espace, tab, \n)
		 *
		 * Si oui → on n'est plus dans un mot
		 */
		else if (is_separator(*str))
		{
			in_word = 0;  /* on sort du mot */
		}
		/*
		 * CONDITION 3 (implicite) : On continue dans le mot
		 *
		 * Si c'est une lettre ET on était déjà dans un mot
		 * → on ne fait rien, on continue juste
		 */

		/*
		 * str++ = avancer au caractère suivant
		 *
		 * "hello"
		 *  ^      → str pointe ici
		 *  
		 * après str++ :
		 * "hello"
		 *   ^     → str pointe ici maintenant
		 */
		str++;
	}

	/* On retourne le nombre total de mots */
	return (count);
}

/**
 * extract_word - extrait un mot à partir de la position index
 * @str: la chaîne complète
 * @index: pointeur vers la position actuelle (sera modifié)
 *
 * Return: le mot extrait (malloc), ou NULL si erreur
 */
static char *extract_word(char *str, int *index)
{
	char *word;
	int start;
	int len;
	int i;

	/*
	 * VARIABLES :
	 * word  = le mot qu'on va extraire (malloc)
	 * start = position du premier caractère du mot
	 * len   = longueur du mot
	 * i     = pour copier caractère par caractère
	 *
	 * index = pointeur vers notre position dans str
	 *         on utilise *index pour lire/modifier la valeur
	 *         comme ça la fonction appelante sait où on en est
	 */

	/*
	 * ÉTAPE 1 : SAUTER LES SÉPARATEURS
	 * --------------------------------
	 * Si on est sur des espaces, on avance jusqu'à une lettre
	 *
	 * Exemple : "   hello world"
	 *            ^^^
	 *            on saute ces espaces
	 */
	while (str[*index] != '\0' && is_separator(str[*index]) == 1)
	{
		/*
		 * str[*index] = le caractère à la position *index
		 * 
		 * Si c'est un séparateur, on avance
		 * (*index)++ = on incrémente la valeur pointée par index
		 */
		(*index)++;
	}

	/*
	 * ÉTAPE 2 : MÉMORISER LE DÉBUT DU MOT
	 * -----------------------------------
	 * Maintenant *index pointe sur la première lettre du mot
	 * On sauvegarde cette position
	 *
	 * Exemple : "   hello world"
	 *               ^
	 *               start = 3
	 */
	start = *index;

	/*
	 * ÉTAPE 3 : CALCULER LA LONGUEUR DU MOT
	 * -------------------------------------
	 * On avance tant qu'on est sur des lettres (pas séparateur)
	 * On compte chaque lettre
	 *
	 * Exemple : "   hello world"
	 *               ^^^^^
	 *               len = 5
	 */
	len = 0;
	while (str[*index] && !is_separator(str[*index]))
	{
		len++;        /* une lettre de plus */
		(*index)++;   /* avancer au caractère suivant */
	}

	/*
	 * ÉTAPE 4 : ALLOUER LA MÉMOIRE POUR LE MOT
	 * ----------------------------------------
	 * On a besoin de len + 1 caractères
	 * +1 pour le '\0' à la fin
	 *
	 * Exemple : "hello" → 5 lettres + 1 '\0' = 6 octets
	 */
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);  /* malloc a échoué */

	/*
	 * ÉTAPE 5 : COPIER LE MOT
	 * -----------------------
	 * On copie depuis str[start] vers word
	 *
	 * Exemple :
	 * str   = "   hello world"
	 *             ^^^^^
	 *             start=3, on copie 5 caractères
	 *
	 * word  = "hello\0"
	 */
	i = 0;
	while (i < len)
	{
		/*
		 * str[start + i] = caractère source
		 * word[i] = destination
		 *
		 * i=0 : word[0] = str[3] = 'h'
		 * i=1 : word[1] = str[4] = 'e'
		 * i=2 : word[2] = str[5] = 'l'
		 * i=3 : word[3] = str[6] = 'l'
		 * i=4 : word[4] = str[7] = 'o'
		 */
		word[i] = str[start + i];
		i++;
	}

	/*
	 * ÉTAPE 6 : TERMINER LA STRING
	 * ----------------------------
	 * On ajoute '\0' à la fin pour en faire une string C valide
	 *
	 * word = "hello\0"
	 *              ^
	 *              word[5] = '\0'
	 */
	word[i] = '\0';

	/*
	 * On retourne le mot extrait
	 * 
	 * IMPORTANT : *index a été modifié !
	 * Il pointe maintenant APRÈS le mot
	 * Comme ça le prochain appel commencera au bon endroit
	 */
	return (word);
}
/**
 * ft_split_to_av - découpe une string en tableau d'arguments
 * @str: la chaîne à découper (vient de getline par exemple)
 *
 * Return: tableau de strings (NULL terminated), ou NULL si erreur
 */
char **ft_split_to_av(char *str)
{
	char **av;
	int word_count;
	int index;
	int i;

	/*
	 * VARIABLES :
	 * av         = le tableau de strings qu'on va retourner
	 * word_count = combien de mots dans la chaîne
	 * index      = notre position dans str
	 * i          = pour remplir av[0], av[1], av[2]...
	 */

	/*
	 * PROTECTION : si str est NULL, on retourne NULL
	 */
	if (str == NULL)
		return (NULL);

	/*
	 * ÉTAPE 1 : COMPTER LES MOTS
	 * --------------------------
	 * On appelle count_words pour savoir combien de mots
	 * On en a besoin pour malloc le bon nombre de cases
	 *
	 * Exemple : "ls -la /home" → word_count = 3
	 */
	word_count = count_words(str);

	/*
	 * ÉTAPE 2 : ALLOUER LE TABLEAU
	 * ----------------------------
	 * On a besoin de word_count + 1 cases
	 * +1 pour le NULL final (comme argv)
	 *
	 * Exemple avec 3 mots :
	 * av[0] = "ls"
	 * av[1] = "-la"
	 * av[2] = "/home"
	 * av[3] = NULL      ← le +1 c'est pour ça
	 *
	 * sizeof(char *) = taille d'un pointeur
	 */
	av = malloc(sizeof(char *) * (word_count + 1));
	if (av == NULL)
		return (NULL);  /* malloc a échoué */

	/*
	 * ÉTAPE 3 : EXTRAIRE CHAQUE MOT
	 * -----------------------------
	 * On boucle word_count fois
	 * À chaque tour, on extrait un mot et on le met dans av[i]
	 */
	index = 0;  /* on commence au début de str */
	i = 0;      /* on remplit av[0], puis av[1], etc. */

	while (i < word_count)
	{
		/*
		 * extract_word(str, &index) :
		 * - extrait le prochain mot
		 * - modifie index pour pointer après le mot
		 *
		 * On passe &index (adresse) pour que extract_word
		 * puisse modifier notre variable index
		 */
		av[i] = extract_word(str, &index);

		/*
		 * GESTION D'ERREUR :
		 * Si malloc a échoué dans extract_word,
		 * on doit libérer tout ce qu'on a déjà alloué
		 */
		if (av[i] == NULL)
		{
			/* Libérer les mots déjà alloués */
			while (i > 0)
			{
				i--;
				free(av[i]);
			}
			/* Libérer le tableau */
			free(av);
			return (NULL);
		}

		i++;  /* passer à la case suivante */
	}

	/*
	 * ÉTAPE 4 : TERMINER PAR NULL
	 * ---------------------------
	 * Convention de argv : le dernier élément est NULL
	 * C'est comme ça qu'on sait où s'arrête le tableau
	 */
	av[i] = NULL;

	/*
	 * On retourne le tableau complet
	 *
	 * Exemple avec "ls -la /home" :
	 * av[0] = "ls"
	 * av[1] = "-la"
	 * av[2] = "/home"
	 * av[3] = NULL
	 */
	return (av);
}
/**
 * main - teste ft_split_to_av avec getline
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n;
	char **av;
	int i;

	/* Afficher le prompt */
	printf("$ ");
	fflush(stdout);

	/* Lire la ligne */
	n = getline(&line, &len, stdin);
	if (n == -1)
	{
		free(line);
		return (1);
	}

	/* Découper en arguments */
	av = ft_split_to_av(line);
	if (av == NULL)
	{
		free(line);
		return (1);
	}

	/* Afficher le résultat */
	i = 0;
	while (av[i] != NULL)
	{
		printf("av[%d] = [%s]\n", i, av[i]);
		i++;
	}

	/* Libérer la mémoire */
	i = 0;
	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
	free(line);

	return (0);
}
