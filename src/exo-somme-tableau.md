% Programmation: Exercice "somme et moyenne d'un tableau".
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 9 juin 2020


![](https://i.creativecommons.org/l/by-nc-sa/2.0/fr/88x31.png)
Ce texte fait partie d'une petite [collection de notes](index.html)
mise à disposition selon les termes de la 
[Licence Creative Commons
Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes
Conditions 2.0
France](http://creativecommons.org/licenses/by-nc-sa/2.0/fr/).


Ces exercices sont souvent proposés aux débutants dans les tutoriels,
pour l'apprentissage des fonctions et des tableaux. Le problème, c'est
qu'ils sont souvent très mal posés. 

- Dans une première partie, on rappelle le texte des exercices, en
essayant de les poser correctement.

- Dans une seconde partie, pour ceux que ça intéresse, on explique pourquoi 
et comment ils sont souvent mal posés.



# Exercices

Ils sont ici énoncés en C, il est facile de les transposer dans
d'autres langages.

Contexte de l'exercice : le débutant

- sait faire lire/afficher des données,
- connait les bases sur un tableau (déclaration, indiçage),
- a vu la notion de boucle sur un intervalle (et parcours séquentiel d'un tableau),
- a eu un exposé sur les fonctions (appel, retour, passage de
  paramètres).

Les exercices sont là pour mettre en pratique les fonctions.

## Somme des éléments d'un tableau

Écrivez une fonction nommée `somme_tableau` qui retourne la somme des
éléments d'un tableau.

Elle prend comme paramètre

- un tableau de nombre réels (type `double`),
- le nombre d'éléments de ce tableau.

Par exemple le programme de tests

~~~C
#include <stdio.h>

int main()
{
	printf("Tests somme\n");
	
	double t1[] = {20.5, -3.0 , 4.5}; 
    double r1 = somme_tableau(t1, 3);
	printf("r1 = %f\n", r1);
	
	double t2[] = {13.0, 7.5, 18, 12, 13.5, 9 };
	double r2 = somme_tableau(t2, 6);
	printf("r2 = %f\n, r2);
	
	return 0;
}
~~~

complèté par la fonction demandée, devrait afficher :

~~~
Tests somme:
r1 = 22.000000
r2 = 73.000000
~~~


## Moyenne d'un tableau

En utilisant la fonction précédente, écrivez une fonction qui calcule
la moyenne des éléments d'un tableau.  Elle prend elle aussi comme
paramètres

- un tableau de nombres réels,
- le nombre d'éléments

Avec l'exemple d'utilisation : 

~~~C
    printf("Tests moyenne :\n");
	double m1 = moyenne_tableau(t1, 3);
	printf("m1 = %f\n", m1);
~~~

on s'attend à obtenir :

~~~
Tests moyenne :
m1 = 7.333333
~~~

Testez aussi sur l'autre exemple.




# Problèmes pédagogiques fréquents rencontrés

## Calcul de la somme

- Absence d'insistance sur le fait que la fonction doit **retourner**
  une valeur. Donc, pour faire comme dans les exercices précédents, le
  débutant fait **afficher** un résultat dans la fonction.
- **Absence de code de test**. L'apprenti programmeur est incité à faire
  une boucle de lecture interactive, à laquelle il ajoute une boucle
  d'écriture. Et mélange donc saisie, calcul et affichage.
- **Un seul exemple de test**, par exemple avec un tableau de 4 éléments.
Ne permet pas de réaliser que la fonction est faite pour travailler
avec divers tableaux, de tailles diverses. Se traduit par une boucle
avec borne "en dur".
- Test donné avec des **valeurs fantaisistes** (trop grandes) dont la
  somme n'est pas indiquée. Le débutant sera content dès qu'il
  s'affiche un nombre, qu'il ne fera pas l'effort de vérifier.
- Tableau contenant des **zeros au début ou à la fin**, ne permettant pas
de remarquer les erreurs de début ou fin de boucle.


## Calcul de la moyenne

- Exercice proposé sur un  **tableau d'entiers**, sans indiquer que
le résultat attendu est un flottant.
- Oblige à disgresser
  sur les problèmes de conversion d'entier à réel.
- Oubli d'insister sur l'emploi de la fonction `somme_tableau` déjà
  écrite. Le débutant s'imagine souvent que le but de l'exercice est
  d'écrire une **variante** du code existant (de la même façon qu'on
  pose des exercices de maths similaires, avec des coefficients
  différents).
    
