# Simple Shell

Un shell simple écrit en C, implémentant les fonctionnalités basiques d'un interpréteur de commandes Unix/Linux. Ce projet est réalisé dans le cadre du cursus Holberton School.

## 📋 Description

Ce projet est une implémentation simplifiée d'un shell Unix, capable de :
- Lire et interpréter des commandes utilisateur
- Exécuter des programmes externes
- Gérer les variables d'environnement
- Gérer les commandes intégrées (`env`, `exit`)
- Fonctionner en mode interactif et non-interactif

## 🏗️ Architecture du Projet

Le projet est structuré en plusieurs fichiers modulaires :

| Fichier | Description |
|---------|-------------|
| `main.c` | Point d'entrée du shell, boucle principale |
| `shell.h` | Fichier d'en-tête avec déclarations des fonctions |
| `execute.c` | Exécution des commandes (fork et exec) |
| `tokenize.c` | Tokenisation des lignes de commande |
| `process.c` | Traitement et dispatching des commandes |
| `prompt.c` | Affichage du prompt |
| `env.c` | Gestion des variables d'environnement |
| `exit.c` | Gestion de la commande exit |

## 🚀 Utilisation

### Compilation

```bash
gcc -Wall -Wextra -Werror *.c -o shell
```

### Exécution

**Mode interactif :**
```bash
./shell
```

**Mode non-interactif :**
```bash
echo "ls -la" | ./shell
./shell < commandes.txt
```

## 📝 Fonctionnalités Implémentées

### Commandes Intégrées
- **`env`** : Affiche les variables d'environnement
- **`exit`** : Quitte le shell

### Fonctionnalités
- Prompt personnalisé en mode interactif
- Exécution de commandes externes
- Gestion des variables d'environnement
- Tokenisation des arguments
- Gestion des erreurs de commande introuvable

## 💡 Exemple d'Utilisation

```bash
$ ./shell
$ ls -la
total 48
-rw-r--r-- 1 user user   126 Dec 30 11:00 README.md
-rwxr-xr-x 1 user user  5432 Dec 30 11:00 shell
...

$ echo hello world
hello world

$ env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin
HOME=/home/user
...

$ exit
```

## 📚 Structure de la Boucle Principale

1. Affichage du prompt (si mode interactif)
2. Lecture de la ligne de commande
3. Tokenisation en arguments
4. Traitement (commande intégrée ou externe)
5. Exécution et attente de fin de processus
6. Retour à l'étape 1

## 🔧 Compilation avec les Flags Requis

```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o shell
```

- `-Wall` : Affiche tous les avertissements
- `-Wextra` : Avertissements supplémentaires
- `-Werror` : Les avertissements sont traités comme des erreurs
- `-pedantic` : Conformité stricte avec le standard C

## 📝 Auteur

Projet Holberton School - Matéo

## 📄 License

Ce projet est fourni à titre éducatif.
