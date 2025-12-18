#include <stdio.h>   /* printf, perror */
#include <fcntl.h>   /* open, O_RDONLY */
#include <unistd.h>  /* read, close */

/**
 * main - affiche le PPID en lisant /proc/self/stat
 *
 * Return: 0 en cas de succès, 1 sinon
 */
int main(void)
{
	char buf[512];   /* buffer pour stocker le contenu du fichier */
	int fd;          /* file descriptor - "numéro" du fichier ouvert */
	int i;           /* index pour parcourir le buffer */
	int field;       /* va contenir le PPID extrait */
	ssize_t n;       /* nombre d'octets lus par read() */

	/*
	 * ÉTAPE 1 : OUVRIR LE FICHIER
	 * ---------------------------
	 * /proc/self/stat = fichier virtuel contenant les infos du processus
	 * /proc = système de fichiers virtuel du noyau Linux
	 * self  = lien vers le PID du processus actuel
	 * stat  = statistiques du processus
	 *
	 * O_RDONLY = ouvrir en lecture seule (Read Only)
	 *
	 * open() retourne :
	 *   - un fd >= 0 si succès (généralement 3, car 0/1/2 sont stdin/stdout/stderr)
	 *   - -1 si erreur
	 */
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("open");  /* affiche l'erreur système */
		return (1);
	}

	/*
	 * ÉTAPE 2 : LIRE LE CONTENU
	 * -------------------------
	 * read(fd, buffer, taille_max)
	 *
	 * fd           = le fichier ouvert
	 * buf          = où stocker les données lues
	 * sizeof(buf)-1 = lire max 511 octets (garder 1 place pour '\0')
	 *
	 * read() retourne :
	 *   - nombre d'octets lus si succès
	 *   - 0 si fin de fichier (EOF)
	 *   - -1 si erreur
	 */
	n = read(fd, buf, sizeof(buf) - 1);

	/*
	 * ÉTAPE 3 : FERMER LE FICHIER
	 * ---------------------------
	 * Toujours fermer après utilisation !
	 * Libère le file descriptor pour le système
	 */
	close(fd);

	if (n <= 0)
	{
		perror("read");
		return (1);
	}

	/*
	 * ÉTAPE 4 : TERMINER LA STRING
	 * ----------------------------
	 * read() ne met PAS de '\0' à la fin
	 * On doit le faire nous-mêmes pour avoir une string C valide
	 *
	 * Exemple : si read() lit 100 octets, n = 100
	 * On met buf[100] = '\0'
	 */
	buf[n] = '\0';

	/*
	 * ÉTAPE 5 : PARSER LE CONTENU
	 * ---------------------------
	 * Le fichier contient une ligne comme :
	 * "1234 (bash) S 1000 1234 1234 ..."
	 *  ^pid ^nom   ^state ^ppid
	 *
	 * Le nom peut contenir des espaces : "(mon programme)"
	 * Donc on cherche la DERNIÈRE parenthèse fermante ')'
	 */
	i = 0;
	while (buf[i] && buf[i] != ')')
		i++;

	/* Si on n'a pas trouvé ')', fichier mal formaté */
	if (!buf[i])
		return (1);

	i++;  /* avancer après ')' */

	/*
	 * Maintenant buf[i] pointe sur : " S 1000 ..."
	 *                                 ^ ici
	 *
	 * Structure après ')' :
	 * [espace(s)] [state] [espace(s)] [ppid] ...
	 */

	/* Sauter les espaces entre ')' et state */
	while (buf[i] == ' ')
		i++;

	/* Sauter le state (c'est UN seul caractère : R, S, D, Z, T...) */
	i++;

	/* Sauter les espaces entre state et ppid */
	while (buf[i] == ' ')
		i++;

	/*
	 * ÉTAPE 6 : CONVERTIR LE PPID EN INT
	 * ----------------------------------
	 * buf[i] pointe maintenant sur le premier chiffre du PPID
	 * Ex: "1000 1234 ..."
	 *      ^ ici
	 *
	 * Algorithme de conversion string -> int :
	 * "1000" -> 1*1000 + 0*100 + 0*10 + 0*1
	 *
	 * En itératif :
	 * field = 0
	 * field = 0 * 10 + 1 = 1
	 * field = 1 * 10 + 0 = 10
	 * field = 10 * 10 + 0 = 100
	 * field = 100 * 10 + 0 = 1000
	 */
	field = 0;
	while (buf[i] >= '0' && buf[i] <= '9')  /* tant que c'est un chiffre */
	{
		field = field * 10 + (buf[i] - '0');
		/*
		 * buf[i] - '0' convertit le caractère en valeur numérique
		 * '0' = 48 en ASCII
		 * '5' = 53 en ASCII
		 * '5' - '0' = 53 - 48 = 5
		 */
		i++;
	}

	printf("%d\n", field);

	return (0);
}
