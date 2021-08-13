% L'éditeur vi, utilisation minimale.
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 7 juin 2020


![](https://i.creativecommons.org/l/by-nc-sa/2.0/fr/88x31.png)
Ce texte fait partie d'une petite [collection de notes](index.html)
mise à disposition selon les termes de la 
[Licence Creative Commons
Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes
Conditions 2.0
France](http://creativecommons.org/licenses/by-nc-sa/2.0/fr/).


# Pourquoi ce document ?


Apparu en 1976, l'éditeur de textes `vi` est présent
sur la majorité des systèmes Unix (`vim`, version améliorée).
C'est parfois le seul éditeur installé au départ, et souvent
l'éditeur de textes par défaut pour certaines commandes (`git`, par exemple) qui demandent à modifier un texte.

On peut en préférer légitimement d'autres (`emacs`, par exemple !), mais
il est important :

- de savoir en sortir si on est tombé dedans involontairement,
- de connaître quelques commandes de bases pour l'utiliser, même si on
  préférerait autre chose.

Le but de ce document est de vous montrer très rapidement le strict
minimum pour, disons, modifier un petit fichier texte sur une machine
où votre éditeur favori n'est pas (ou pas encore) installé.
Il y a bien sûr beaucoup plus de choses à savoir pour l'utiliser
efficacement.


# Un éditeur modal

L'éditeur `vi` est destiné à être utilisé avec un écran alphanumérique
(texte seulement, pas de graphique) ou une émulation de terminal.

Quand on l'ouvre, on voit le texte que l'on édite, et une ligne d'état
en bas.  Dans le texte, le curseur (sous forme de bloc) clignote. La
fin du texte est marquée par des "tildes" en première position.

![L'éditeur `vi` dans un terminal](images/capture-vi.png)

C'est un éditeur de textes visuel `modal`, c'est-à-dire que l'effet de
ce qu'on tape dépend du mode où on se trouve. Par exemple, taper un caractère
`e` :

- en mode "normal", amène le curseur en fin de mot (e comme end),
- en mode "insertion", insère un `e` à la position du curseur, qui se déplace.

Il y a d'autres modes à connaître

- le mode "command line" qui permettra de sauver et de quitter
- le mode "replace" dans lequel ce qu'on tape remplace ce qui est déjà là
- le mode "visual" qui permettra de faire du couper/copier/coller.

**Pas de panique** pour s'y retrouver:

- le mode courant est affiché en bas de l'écran,
- au départ on est en mode normal,
- la touche d'échappement fait toujours revenir au mode courant.

# Sortir de `vi`, le mode *command-line*.

Pour sortir de `vi`, le principe est de passer en mode "command line"
(touche "`:`") pour  taper la commande `q` puis Entrée.

En pratique, vous avez tapé au hasard sur des touches, et donc 
vous ne savez pas dans quel mode vous êtes. Donc

1. faites ESC pour **revenir en mode normal**,
2. tapez "`:`" pour passer en mode "command line".
3. tapez la commande "`q!`" puis la touche Entrée.

Pourquoi le point d'exclamation ? Si en tapant au hasard, vous avez
inséré des caractères involontairement dans le "tampon d'édition",
`vi` ne vous laisse pas sortir sans avoir sauvegardé.  Le point
d'exclamation après le `q` sert à insister.

Si vous n'aviez fait qu'entrer dans `vi`, il suffisait de faire 

> `:q` Entrée

# Mode normal : se déplacer

L'éditeur `vi` a été conçu pour un usage intensif par les
programmeurs.  Ceci exclut l'emploi de la souris (peu fréquente en
1976) qui, si elle rassure les débutants, ralentit énormément le
travail à cause du déplacement de l'avant bras, et de la coordination
nécessaire entre yeux et main.

Le minimum à savoir : 

- Les 4 touches`hjkl` déplacent le curseur d'une position. (h à
  gauche, j en bas, k en haut, l à droite).
- les touches flèche marchent aussi (même si leur usage est déconseillé parce
que trop loin des autres touches). 

Un peu plus :

- Contrôle-flèche (avant ou arrière) pour se déplacer d'un mot.
- controle-F et controle-B pour avancer/reculer (forward/backward) d'un écran.


# Mode normal : annulation

Avant d'aller plus loin, il est important de savoir qu'en cas de
fausse manipulation, on peut annuler des dernières modifications par
`u` (*undo*).


# Mode insertion : ajout et modification de texte.

On passe du mode normal au mode insertion en tapant "`i`" (pour
*insert*).

Le texte qu'on tape ensuite est inséré avant l'emplacement du curseur.

Quelques autres touches utilisables :

- les flèches pour se déplacer
- "espace arrière" pour supprimer le caractère à gauche du curseur,
- "Suppr" pour supprimer le caractère du curseur.

En fin de ligne, vous trouverez peut-être plus pratique d'ajouter
**après** le curseur, avec "`a`" (*append*) au lieu de "`i`".


Le mode "replace" est similaire, sinon qu'on y rentre par "`R`", et
que ce qu'on tape remplace ce qui est déjà là, et que la touche
"espace arrière" annule la dernière frappe.


# Couper/copier/coller : mode "visuel"

Pour **copier** :

1. se mettre en mode normal,
2. se déplacer au début de la zone à copier
3. taper "`v`"pour passer en mode visuel,
4. se déplacer (les caractères entre le début et le curseur
   apparaissent différemment, d'où le terme de "visuel"),
5. à la fin de la zone, taper "`y`", qui sauvegarde la zone dans un
   tampon (*to yank* : arracher, tirer d'un coup sec).
   
Pour **couper** au lieu de copier : 

5. faire `d` (*delete*) au lieu de `y`.

Dans les deux cas, on est revenu en mode normal. 

Pour **coller** ce qui a sauvegardé

6. se déplacer à l'endroit voulu,
7. taper `P` ou `p` pour insérer avant le curseur, ou après.

# Sauver (mode commande)

Pour sauver, on passe en mode commande (Échappement + "`:`").

- la commande `w` sauve le tampon d'édition dans le fichier associé,
- la commande `wq` sauve et quitte.
- on peut sauver dans un fichier diffèrent en mettant son nom après un espace, exemple

>  ESC:wq final.txt [Entree]


# Recherche incrémentale

Pour finir, si vous cherchez quelque chose dans le texte :

1. passez en mode normal (échappement) ; 
2. tapez "`/`" puis le début de ce que vous cherchez. La recherche est
incrémentale (le curseur se déplace quand vous complétez votre critère
de recherche) ;
3. la touche Entrée met fin à la recherche.

En plus, en mode normal, 

- la touche `n` (next) permet de chercher l'occurrence suivante,
- la touche `N` amène sur la précédente.


Le critère de recherche peut être une expression régulière. C'est un
autre sujet.


