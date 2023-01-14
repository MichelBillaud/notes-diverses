% Réalisation d'un pipeline rb
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

La réalisation d'un tel programme n'est pas très compliquée.

Là où ça se complique un peu, c'est si on demande que le shell
permette d'exécuter des "pipelines" de commandes, c'est-à-dire de
lancer plusieurs commandes en redirigeant la sortie de l'une vers
l'autre, comme dans

~~~bash
ls -l | grep -v ^d | more
~~~

La difficulté est essentiellement d'utiliser correctement les
$n-1$ tuyaux qui interviennent dans un "pipeline" de $n$ commandes.

Nous allons voir après quelques rappels.


# Rappels

## Exécuter une commande : `exec`

Le programme suivant

- affiche un message
- fait exécuter la commande `ls /tmp` au moyen de `execv`.


~~~C
// demo-exec.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("# lancement " __FILE__ "\n");

    char *path = "/bin/ls";
    char *arguments[] = { "ls", "/tmp", NULL};

    execv(path, arguments);

    perror("échec lancement");
    exit(EXIT_FAILURE);
}
~~~

La commande `execv` prend comme paramètres

- le chemin d'accès d'un fichier exécutable
- une liste de paramètres terminée par le pointeur `NULL`.

### Succès de `execv()`

Normalement le fichier indiqué (`/bin/ls`) sera chargé dans
la mémoire du processus en remplacement du code de `demo-exec`, et sa
fonction `main`, qui a comme prototype `int main(int argc, char
**argv)` sera appelée avec

- l'adresse du tableau d'arguments dans `argv` (argument values)
- la valeur 2 dans `argc` (argument count)

Le code qui s'exécute ayant été remplacé, la fin de l'exécution de
`/bin/ls` termine le processus : on ne revient pas de `execv`.

### Echec de `execv()

Si le fichier indiqué en premier paramètre est absent, pas accessible,
pas exécutable etc. l'appel à `execv` retourne, et les instructions
suivantes sont exécutées.

C'est l'occasion d'afficher un message d'erreur.

## Remarques

- La valeur retournée par `execv` est `-1`, mais peu importe : on sait
que si on est ressorti d'`execv` c'est que le lancement du programme
n'a pas pu se faire.
- ne pas confondre "le lancement a échoué" (dans ce cas `execv`
retourne), et "l'exécution du programme lancé a échoué" (le programme
lancé s'est effectivement exécuté, et s'est terminé par `exit` en
retournant un code non nul).


## Redirection : `dup2`

La plupart des commandes

- lisent des données sur leur entrée standard (`stdin`), qui a le
  descripteur 0,
- écrivent des résultats sur le sortie standard (`stdout`, descripteur
  1),
- affichent des messages sur la sortie d'erreur (`stderr`, descripteur
  2).

L'exemple ci-dessous utilise l'appel `dup2` pour que la commande `tr`
(avec les paramètres pour convertir les minuscules en majuscules),
s'exécute avec son entrée standard connectée à un fichier  :


~~~C
// demo-exec-dup.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    printf("# lancement " __FILE__ "\n");

    char *path = "/bin/tr";
    char *arguments[] = { "tr", "a-z", "A-Z",  NULL};
    
    int fd = open("demo-exec-dup.c", O_RDONLY);
    dup2(fd, 0);
    close(fd);
    
    execv(path, arguments);

    perror("échec lancement");
    exit(EXIT_FAILURE);

}
~~~


**Explications :**

- L'appel à la fonction `open` ouvre le fichier en lecture,
- Pour chaque fichier ouvert, il y a une structure de données qui
contient un tampon, une indication de l'endroit où on est de la
lecture ou de l'écriture, etc.
- Cette structure de données est identifiée par un numéro, le
  **descripteur de fichier** ouvert. En général le plus petit numéro non
  utilisé, sans doute 3 ici.
- L'appel `dup2(fd, 0)`  fait en sorte que le descripteur 0 conduise au
même fichier que le 3 (le descripteur 0 est fermé préalablement).
- Les descripteurs ouverts le restent lors de l'appel de `execv` : la
commande `tr` s'exécute donc avec son entrée standard (0) reliée au
fichier de données.
- Préalablement, un `close` de `fd` évite une **fuite de
descripteur** : on ne veut transmettre que les descripteurs 0, 1 et 2.

C'est ce problème de fuite de descripteur qui complique le problème de
réalisation d'un pipeline.

**Exécution** :

Le programme affiche le code source en majuscules :

~~~
# lancement demo-exec-dup.c
// DEMO-EXEC-DUP.C

#INCLUDE <STDIO.H>
#INCLUDE <STDLIB.H>
...
    EXIT(EXIT_FAILURE);

}
~~~

## Lancer un processus : `fork` + `waitpid`

Comme l'exécution d'une commande par `execv` termine le processus en
cours, on va avoir un problème si on veut faire exécuter *plusieurs*
commandes.

La solution est de faire exécuter chaque commande par un processus
créé à cet effet.

~~~C
// demo-fork.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>

void execute_task()
{
    char *path = "/bin/tr";
    char *arguments[] = { "tr", "a-z", "A-Z",  NULL};
    int fd = open("demo-fork.c", O_RDONLY);
    dup2(fd, 0);
    close(fd);
    execv(path, arguments);
    // en cas de problème pour lancer tr
    perror("erreur lancement commande tr");
    exit(EXIT_FAILURE);
}

void explain_status(int child_status)
{
    printf("# La commande s'est terminée ");
    if (WIFEXITED(child_status)) {
        printf("par exit(%d)\n", WEXITSTATUS(child_status));
    } else if (WIFSIGNALED(child_status)) {
        printf("par la réception du signal %d\n", WTERMSIG(child_status));
    } else {
        printf("pour une raison x ou y.\n");
    }
}

int main(int argc, char *argv[])
{
    pid_t child_pid = fork();
    if (child_pid == 0) {
        execute_task();
        assert("on ne revient jamais ici" && false);
    }
    int child_status;
    waitpid(child_pid, &child_status, 0);

    explain_status(child_status);
    exit(EXIT_SUCCESS);
}
~~~~

L'exécution montre ceci :

~~~
// DEMO-FORK.C

#INCLUDE <STDIO.H>
#INCLUDE <STDLIB.H>
....
    EXPLAIN_STATUS(CHILD_STATUS);
    EXIT(EXIT_SUCCESS);
}
# La commande s'est terminée par exit(0)
~~~

**Explications** brèves (qui ne remplacent pas un cours)


1. L'appel à `fork()` démarre un nouveau processus (dit "fils") qui est
une copie du processus en cours d'exécution (son "père").
	- les deux processus partagent les ressources (descripteurs de
      fichiers),
	- `fork()` retourne au père l'identifiant du processus fils, et 0
      à celui-ci.

Le processus fils appelle donc la fonction `execute_task()`, tandis
que le processus père qui a reçu l'identifiant non nul de son fils ne
rentre pas dans le corps du `if`.                                          

2. La fonction `execute_task()` - exécutée par le fils - lance la
  commande `/bin/tr` comme dans l'exemple précédent. On 
  ne revient
  jamais de cette fonction qui  lance `/bin/tr` par `execv`, ou
    `exit(EXIT_FAILURE)` en cas d'échec.


3. En même temps (à peu près) le processus père 
  - exécute `waitpid` qui le bloque en attendant la fin de
    l'exécution du fils,
  - affiche ensuite des messages et se termine.
  
4. Le second paramètre de `waitpid` est l'adresse d'un entier
qui contiendra les informations sur la fin du processus fils. Dans
`explain_child_status`, diverses macros permettent
	- de savoir si il s'est terminé par `exit()` ou en recevant un
      signal qui a provoqué sa fin,
	- de connaitre le code de retour dans le premier cas, ou le numéro
      du signal.



## Faire communiquer deux commandes par `pipe`


Un "tuyau" est un pseudo-fichier géré par le système d'exploitation.
C'est un tampon en mémoire dans lequel on peut écrire et lire. Il sert
à la communication entre processus issus d'un même père.  Les données
sont lues dans l'ordre où elles ont été écrites dans le tuyau.

Un tuyau a une capacité limitée. Un processus qui veut écrire plus de
   données dans le tuyau qu'il ne peut en contenir sera bloqué en
   attendant qu'il y ait suffisamment de place.

Le tuyau est créé par un appel à la commande `pipe` qui retourne -
dans un tableau donné en paramètre - deux descripteurs : celui qui
sert à lire dans le tuyau, et celui qui sert à y écrire.

Plusieurs processus peuvent lire et/ou écrire dans un même tuyau,
pourvu qu'ils disposent d'un descripteur ouvert qui permet
l'opération.


**Important** : En lecture, on atteint la "**fin de fichier**" quand
il n'y a plus de données disponibles dans le tuyau, **et que tous les
descripteurs d'écriture ont été fermés**.
   
Pour chaque processus, il faudra donc faire très attention à bien
refermer tous les descripteurs (surtout d'écriture) dont on ne se sert
pas. Sinon un processus en lecture pourra rester bloqué indéfiniment,
en attente de données que personne ne lui enverra.




**L'exemple** qui suit équivaut au lancement de la commande shell :

~~~bash
date | wc a-z A-Z
~~~

qui affiche la date mise en majuscules

~~~
SAM. 14 JANV. 2023 18:50:22 CET
~~~

Voici le source :

~~~C
// demo-pipe.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd[2];
    
    pipe(fd);

    pid_t date_pid = fork();
    if (date_pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execv("/bin/date", (char *[]){"date", NULL}); 
        perror("échec lancement de date");
        exit(EXIT_FAILURE);
    }
    
    pid_t tr_pid = fork();
    if (tr_pid == 0) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execv("/bin/tr", (char *[]){"tr", "a-z", "A-Z", NULL}); 
        perror("échec lancement de tr");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(date_pid, NULL, 0);
    waitpid(tr_pid, NULL, 0);
    
    exit(EXIT_SUCCESS);
}
~~~


**Explications** :

- la commande `pipe(fd)` crée un tuyau et place les descripteurs dans le
tableau
- le premier fils hérite des deux descripteurs 
	- il duplique le descripteur d'écriture, pour que la sortie de la
      commande `date` se fasse dans le tuyau ;
	- il ferme ensuite les descripteurs du tuyau.
- le premier fils hérite aussi des deux descripteurs 
	- il duplique le descripteur de lecture, pour que la commande `tr`
	prenne son entrée dans le tuyau
	-  il ferme ensuite les descripteurs du tuyau
- une fois les fils lancés, le processus père 
  - ferme les descripteurs du tuyau (il n'en n'a plus l'usage),
  - attend la fin de l'exécution des deux fils.
  
**Remarque :**

- comme `fd[1]` n'est utilisé que par le premier fils, le
processus père pourrait fermer le descripteur d'écriture `fd[1]` plus
tôt, juste après avoir lancé le premier filsn, ce qui dispenserait
d'avoir à le faire dans aussi le code du second. Mais on a privilégié
la simplicité du code.

**NOTES** :

- il serait sans doute préférable s'employer les constantes 
`STDIN_FILENO` et `STDOUT_FILENO`, dans `dup2(fd[0], STDIN_FILENO);` 
- dans `execv("/bin/tr", (char *[]){"tr", "a-z", "A-Z", NULL});` on
voit un exemple de "tableau anonyme" en C. Le contenu (entre
accolades) est précédé par le type du tableau (entre parenthèses).
- Ici cela permet de résumer l'appel d'`execv` à une seule ligne, sans
botter en touche sur des constantes, pour rendre plus visible la
gestion des descripteurs (`dup2`, `close`) par les processus fils.



----------

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
