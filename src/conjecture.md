% Une Conjecture sur les Mots
% Michel Billaud (michel.billaud@laposte.net)
% 12 janvier 2022

![](https://i.creativecommons.org/l/by-nc-sa/2.0/fr/88x31.png)

Ce texte fait partie d'une petite [collection de notes](index.html)
mise à disposition selon les termes de la [Licence Creative Commons
Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes
Conditions 2.0
France](http://creativecommons.org/licenses/by-nc-sa/2.0/fr/).

- Les notes sont publiées dans  <https://www.mbillaud.fr/notes/>
- Sources dans <https://github.com/MichelBillaud/notes-diverses>


Il y a très longtemps (vers 1988), je m'étais posé un petit problème,
que je n'ai pas réussi à résoudre. Rien d'étonnant, c'était pas dans
mon domaine, et je n'y ai travaillé que mollement. Donc j'ai laissé
tomber rapidement, mais après avoir appelé à l'aide sur Usenet, qui ne
manque pas de gens plus compétents (on en retrouve des traces dans le
newsgroup `comp.theory`, en 1993, mais j'avais dû déjà poser la
question en 1988).



> Given a word $w$, if for each letter $x$ occurring in $w$, there 
> exists non-trivial morphism $f_x$ such that the word obtained by erasing
> all the occurrences of $x$ in $x$ is a fixed point of $f_x$, then there
> exists a non-trivial morphism $f$ such that $w$ is a fixed point of $f$.

Et bon, surprise, on est en 2022, mais apparemment c'est toujours pas résolu.

Bon, peut-être que c'est pas très clair, alors j'explique :

# Quelques définitions 

Je suppose que vous avez quand même entendu parler de mots construits
sur un alphabet. Sinon, c'est pas compliqué

## Mots 


- un **alphabet** c'est un ensemble, donc les éléments sont appelés
  **lettres**. Exemple $A = \{a, b, c, d\}$.
- un **mot**, c'est une séquence de lettres, exemple $abcbad$.
- on appelle traditionnellement **langage** un ensemble de mots (sans
  restriction particulière).
- le mot vide, c'est la séquence vide, qu'on note souvent $\epsilon$
- la **concaténation** de deux mots, c'est quand on les met bout à
  bout. On la note souvent par un point. Par exemple, $ab . cbad =
  abcbad".
- par commodité, on confond la notation d'une lettre avec le mot qui
  ne contient que cette lettre.
  
## Morphisme

En général, un **morphisme** est une application d'un ensemble vers un autre qui
préserve une opération.

Ici on considére les morphismes entre deux ensembles de mots
(construits sur des alphabets différents ou pas) qui préservent la
concaténation.

C'est-à-dire que si $f$ est un morphisme, pour tous mots $u, v$ on a
$f(u.v) = f(u).f(v)$.

Une conséquence est qu'un morphisme est déterminé par la
connaissance des images des lettres de l'alphabet. C'est évident : 
si on connait $f(a)$, $f(b)$ etc. alors on peut calculer l'image des
mots formés à partir des lettres $a, b,...$ etc.


La notion s'étend à des langages (ensembles de mots) : l'image d'un
ensemble de mots par un morphisme, c'est l'ensemble des images par le
morphisme.


## Points-fixes d'un morphisme

On regarde maintenant les morphismes dans le cas où les ensembles de
départ et d'arrivée sont les mêmes. Automorphismes ?

Un **point fixe du morphisme** $f$, c'est un mot $w$ qui est sa propre image par $f$ (c-a-d  $f(w) = w$).

Exemple $ab$ est un point fixe pour $f(a) = ab$ et $f(b) = \epsilon$.

Un morphisme n'admet pas forcément de point fixe, exemple évident : le
morphisme qui double chaque lettre : $f(a) = aa, f(b) = bb, ;...$.

Mais quand il en admet un, il en admet une infinité : si $f(w) = w$,
alors $f(w^n) = w^n$.


# Morphismes qui ont un mot comme point-fixe

On aurait pu s'amuser avec les propriétés de l'ensemble des points fixes d'un
morphisme, mais on part dans la direction inverse :

- on prend un mot $w$ au départ
- quels morphismes l'admettent comme point fixe ?

Ce qui amène quelques observations :

- il y en a toujours au moins un : le
morphisme identité.
- si on en a un, tous les morphismes
obtenus en faisant varier les images des lettres qui n'apparaissent pas 
dans le mot font aussi l'affaire. 

Exemple : si on part du mot $w = aa$, on a $f(w)=w$ si et seulement si
$f(a) = a$. Les valeurs de $f(b)$, $f(c)$ etc. sont indifférentes.

On va donc se concentrer sur les morphismes restreints aux lettres qui
apparaissent dans le mot.

## Mots primitifs : qui ne sont points fixes que par l'identité

Ce qui nous intéresse, c'est les mots qui ne sont leur propre image
**que d'une seule et unique façon** : par l'identité.

Exemples : $a$, $aa$, $a^n$, $abba$, $ababa$, $(ab)^na$, etc.

Contre-exemple : $abab$, en prenant $f(a)=ab$ et $f(b)=\epsilon$.


Il est bien évident qu'il y en a une infinité (cf. les exemple $a^b$).

On va les appeler "mots primitifs".

## La conjecture

Informellement, la question c'est 

> tout mot primitif sur un alphabet à $n$ lettres peut-il être obtenu à
partir d'un mot primitif sur un alphabet à $n-1$ lettres, en y
insérant judicieusement des occurrences de la lettre supplémentaire ?

Exemple

- $abba$ : à partir de $aa$ ou $bb$,
- $abcacb$ : à partir de $bccb$, mais pas de $abab$ ou $acac$ qui ne
  sont pas primitifs.


Bref, posé dans l'autre sens : 

> pour tout mot primitif $w$,
> existe-t-il au moins une lettre $x$ dans $w$ qu'on pourrait
> effacer pour retomber sur un mot primitif ?

Les enumérations par programme n'ont jusqu'ici pas trouvé de contre-exemple,
et on conjecture que oui.

Mais la preuve reste à faire.

# Bibliographie

(TODO)



 
