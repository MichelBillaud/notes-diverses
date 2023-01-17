% Réalisation d'un shell en C : le pipeline
% Michel Billaud (michel.billaud@laposte.net)
% 6 janvier 2023
 
# Objectif

La réalisation d'un mini-*shell* (interprète de commandes) est un
projet classique de programmation système en C.

Dans sa version la plus simpliste, un shell est une boucle qui

- affiche une chaîne d'invite (*prompt*),
- lit une commande, 
- lance son exécution,
- et recommence.

Les commandes sont des suites de mots : en général le chemin d'accès
d'un programme (exécutable), suivi par des options, des arguments...

Il y a aussi des commandes dites *internes*, par exemple `exit`, qui
fait arrêter la boucle du shell. Un autre exemple est la commande `cd`
qui change le répertoire courant.

Ce document montre d'abord un point de départ pour la réalisation
d'un tel shell.

Une première version est donnée, qui exécute des commandes simples.
Ensuite on montre comment faire exécuter des "pipelines" de commandes,
la sortie d'une commande alimentant l'entrée de la suivante.


# Version 0 : un shell simple


## Analyse de la ligne

Cette première version n'exécute pas vraiment les commandes,
elle montre essentiellement

- comment faire la boucle avec `getline()`, qui lit une ligne de
  taille arbitraire ;
- comment décomposer la ligne en "tableau d'arguments",

c'est-à-dire à partir d'une ligne comme

> `char ligne = "  /bin/ls   -al  /tmp";`

construire un tableau (alloué dynamiquement)

`char ** tableau = { "/bin/ls", "-al", "/tmp", NULL};`

contenant une copie des différents "mots" de la ligne, et terminé par
un pointeur nul.



~~~C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>

#include <ctype.h>
#include <string.h>

#define SHELL_NAME "Shell Zero V1"


void print_prompt(int numero)
{
    printf("%d> ", numero);
}

/**
 * returns an array of pointers to copies of
 * the "words" extracted from a line.
 *
 * Words in the line are separated by spaces.
 * The array and copies are dynamically allocated. The array
 * contains a NULL pointer after the copies.
 *
 * @param line a nul terminated string
 * @return a dynamically array of pointers do strings
*/

char ** split_line(const char line[])
{
    int nb_args = 0;
    int max_args = 4;
    char **args = malloc(max_args * sizeof(char *));

    const char *start = NULL;

    for (const char *p = line; *p != '\0'; p++) {
        if (start) {
            if (isspace(*p)) { // end of a word detected
                // extend array if needed
                if (nb_args + 1>  max_args) {
                    max_args = 2 * max_args;
                    args = realloc(args, max_args * sizeof(char *));
                }
                // add string copy
                args[nb_args] =  strndup(start, p - start);
                nb_args += 1;
                start = NULL;;
            }
        } else if (! isspace(*p)) { // start of a new word
            start = p;
        }
    }
    assert(start == NULL);
    // no need to worry about the last word, as the line contains a
    // \r ou \n char (which ends the last word) before the nul terminator

    args[nb_args] = NULL;
    return args;
}

void free_array_of_strings(char **args)
{
    for (char **a = args; *a != NULL; a++) {
        free(*a);
    }
    free(args);
}

void fake_execute_command(char ** args)
{
    printf("Execution of\n");
    for (char ** p = args; *p != NULL; p++) {
        printf("- %s\n", *p);
    }
}

int main()
{
    char *line = NULL;
    size_t line_size = 0;
    printf("--- Hello, this is " SHELL_NAME "!\n");

    int numero = 1;
    while (true) {
        print_prompt(numero);

        int length = getline(& line, &line_size, stdin);
        if (length < 0) {
            break;
        }
        char **args = split_line(line);
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                break;
            } else {
                fake_execute_command(args);
            }
            numero += 1;  // doesn't advance if empty command
        }

        free_array_of_strings(args);
    }
    printf("Bye!\n");
	free(line);
    return EXIT_SUCCESS;
}
~~~

##  Compilation

Ce source est compilé avec (notamment) les options 

>  `-std=c17 -D_XOPEN_SOURCE=700`

la dernière permet de disposer de `getline()` et `strndup()` qui ne
font pas pour l'instant partie du standard C "strict", mais de la bibliothèque
standard POSIX.


## Exemple d'exécution

~~~
--- Hello, this is Shell Zero V1!
1> /bin/ls -al /tmp
Execution of
- /bin/ls
- -al
- /tmp
2> 
2> exit
Bye!
~~~



## Faire exécuter une commande

Notre shell analyse la ligne de commande, mais ne lance pas le
programme correspondant.

Pour cela, dans le `main()` on appelle une fonction qui s'en occupe
vraiment :

~~~C
	// fake_execute_command(args);
	execute_command(args);
~~~

### Code de lancement d'une commande

Le code de cette fonction contient plusieurs appels système

~~~C
void execute_command(char **args)
{
    pid_t child_pid = fork();
    if (child_pid == 0) {
        execvp(args[0], args);
        perror("execvp failed"); 
        exit (EXIT_FAILURE);
    }
    waitpid(child_pid, NULL, 0);
}
~~~


qui nécessitent quelques explications. Supposons qu'au moment de
l'exécution, le tableau `args` contient 

> `{ "ls", "-l", "/tmp", NULL}`


- l'appel de la fonction `execvp` charge en mémoire **à la place du
processus qui l'appelle** l'exécutable nommé `"ls"` et si tout va bien
le fait exécuter (appelle son `main`) en lui passant en paramètres le
contenu du tableau.
- parfois les choses se passent mal : la fonction `execvp` échoue si
on lui indique un fichier non exécutable, ou non accessible, etc.
Dans ce cas, on passe à la suite en faisant afficher un message.
  

Dans le cas d'un succès, le processus qui a lancé `execvp` n'est plus
notre shell.

- C'est pour cela qu'on fait lancer `execvp` par un autre processus
dit "processus fils" crée par `fork()` pour l'occasion.
- le processus fils sera transformé en exécution de la commande
"`ls`", mais le processus shell continuera à exister de son côté.
- Le processus "fils" crée par `fork()` est une copie (presque)
intégrale du processus "père" shell.  Ils en sont au même point
d'exécution **sauf que** `fork()` retourne 
	- au processus fils la valeur 0,
	- au processus père le numéro du processus fils,
ce qui permet de les distinguer par le `if`.
- Après avoir lancé le processus fils, le processus père "shell"
attend, par `waitpid`, la fin du processus fils qui exécute la commande.

Pour en revenir au cas d'erreur : après l'affichage d'un message par
`perror()` si `execvp` a échoué, nous forçons la fin du processus fils
en lui faisant appeler `exit()`.

### Résumé

En résumé, les mécanismes Unix utilisés

- `fork()` crée un processus "fils" qui est une copie de
celui qui l'appelle (= père). Il retourne 0 au fils, et le numéro du
fils au père.
- `exit()` termine le processus qui l'appelle.
- `waitpid` bloque un processus (ici le père) en attente de la
fin d'un autre dont on donne le numéro (ici le fils).
- `execvp()` tente de remplacer le processus courant par l'exécution
d'un programme en lui transmettant des arguments. L'exit du programme
terminera le processus. En cas d'échec de lancement (fichier absent,
non exécutable, etc) l'appelant continue.


**Compléments :**


- il existe une famille de fonctions "`exec`".
	- `execv` prend comme paramètre le **chemin d'accès** de
      l'exécutable et un tableau de paramètres ;
	- celle de l'exemple (`execvp`) prend comme paramètre un **nom de
	commande** et un tableau de paramètres.  L'exécutable est cherché
	dans les répertoires indiqués par la variable d'environnement
	`PATH`.
	- Voir aussi `execl` et `execlp` qui utilisent une **liste** de
      paramètres au lieu d'un **tableau**.
- ici on n'a utilisé que le premier paramètre de `waitpid`. 
    - le troisième permet d'attendre un **changement d'état** du
      processus fils (pas seulement sa fin).
    - Le second, si il n'est pas `NULL`, est l'adresse d'un entier qui
permettra par exemple de récupèrer le code laissé par l'`exit` du
processus fils. Avec quelques petites complications, donc on n'en
parle pas pour le moment : voir la page de manuel.


# Pipeline : analyse

Commençons par regarder un exemple de pipeline qui met en oeuvre 4
programmes :

> `A | B | C | D`

pourquoi 4 ? 

- parce que pour évoquer un pipeline, il faut au moins considérer 2
  commandes ;
- parce que la première et la dernière commandes sont des cas
  particuliers qui respectivement lisent dans l'entrée standard, et
  écrivent sur la sortie standard.
- alors que toutes les commandes (sauf la dernière D) écrivent dans un
  tuyau de communication qui est lu par la suivante. Et
  inversement, toutes sauf la première (A) lisent dans un tuyau.
- avec 2 commandes "intermédiaires" B et C, on aura des chances
  d'inférer ce qu'il faut faire avec un nombre quelconque de commandes
intermédiaires.

## Idée de base : 4 processus fils, 3 tuyaux

L'idée de base sera de lancer (par combinaison de `fork` et `exec`) un
processus pour chaque commande, et d'utiliser trois tuyaux T1, T2, T3
pour les faire communiquer

~~~
lancer processus fils:
	exécuter A, qui 
	- lit sur l'entrée standard
	- écrit dans T1

lancer processus fils:
    exécuter B, qui 
	- lit dans T1 
	- écrit dans T2

lancer processus fils:
    exécuter C, qui 
	- lit dans T2 
	- écrit dans T3

lancer processus fils:
    exécuter D, qui 
	- lit dans T4
    - écrit sur la sortie standard

attendre la fin des processus fils.
~~~


## Créer et fermer les tuyaux au bon moment

Détaillons le **lancement du premier** :

1. Le tuyau T1 doit exister avant le lancement du premier
processus fils , puisque le tuyau doit être visible par le second
processus.
2. Le processus A ne lit pas dans T1, le processus fils peut
fermer le bout qui sert à l'écriture.
3. les autres processus ne doivent pas écrire dans ce tuyau : une fois
   le fils lancé, on ferme le bout qui sert l'écriture dans le tuyau.


~~~
créer tuyau T1                         // 1
lancer processus fils:
    fermer T1[1]                       // 2
	exécuter A, qui 
	- lit sur l'entrée standard
	- écrit dans T1[1]
fermer T1[1] et entrée standard
~~~

Le second processus doit lire dans T1 et écrire dans T2. 

1. Il faut donc créer T2 avant de lancer la commande B,
2. la commande B2 ne lit pas dans T2, le processus fils ferme cette
   extrémité
3. les processus suivants ne lisent pas dans T1, et 
n'écrivent pas dans T2.


~~~
créer tuyau T2                         // 1
lancer processus fils:
    fermer T2[1]                       // 2
	exécuter B, qui 
	- lit sur T1[0]
	- écrit dans T2[1]
fermer T1[0] et T2[1]                  // 3
~~~

La situation est similaire pour le troisième

~~~
créer tuyau T3                         // 1
lancer processus fils:
    fermer T3[1]                       // 2
	exécuter C, qui 
	- lit sur T2[0]
	- écrit dans T3[1]
fermer T2[0] et T3[1]                  // 3
~~~

pour la dernière commande, on ne crée pas de tuyau puis qu'on écrit sur la
sortie standard.


~~~
lancer processus fils:
	exécuter D, qui 
	- lit sur T3[0]
	- écrit sur la sortie standard
fermer T3[0]
~~~

## En termes de descripteurs

L'appel systeme `pipe()` d'Unix demande au système
de créer un tuyau et remplit un tableau `T`
avec deux descripteurs :  

- `T[0]` permet la lecture dans le tuyau 
- `T[1]` sert à écrire.

Nous allons nous intéresser aux descripteurs plutot qu'aux tableaux, en 
passant par des variables

~~~C
int entree, sortie;  

int t[2];
pipe(t);
entree = t[0];
sortie = t[1];
~~~

ce que nous abrègerons en écrivant

~~~
créer tuyau (sortie_tuyau, entree_tuyau)
~~~

Une autre variable nous servira à désigner le descripteur
utilisé en lecture par le prochain processus.

Au départ c'est l'entrée standard



~~~
entree = entree_standard

créer tuyau (sortie_tuyau, entree_tuyau) 
lancer processus fils:
    fermer entree_tuyau
	exécuter A, qui 
	- lit sur entree
	- écrit dans sortie_tuyau
fermer sortie_tuyau et entree

~~~


Le code pour les processus B et C n'est pas très différent. 


~~~
entree = entree_tuyau

créer tuyau (sortie_tuyau, entree_tuyau) 
lancer processus fils:
    fermer entree_tuyau
	exécuter B, qui 
	- lit sur entree
	- écrit dans sortie_tuyau
fermer sortie_tuyau et entree

entree = entree_tuyau

créer tuyau (sortie_tuyau, entree_tuyau) 
lancer processus fils:
    fermer entree_tuyau
	exécuter C, qui 
	- lit sur entree
	- écrit dans sortie_tuyau
fermer sortie_tuyau et entree
~~~


Quelques changements pour le dernier

~~~
entree = entree_tuyau

lancer processus fils:
    fermer entree_tuyau
	exécuter C, qui 
	- lit sur entree
	- écrit dans sortie_standard
fermer entree
~~~

