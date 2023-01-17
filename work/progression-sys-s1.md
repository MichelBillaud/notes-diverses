% Progression enseignement système S1
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 13 juin 2020


# Choix : quels exemples pour commencer

**Problématique :** trouver une motivation plausible (pour les étudiants)
pour employer des fichiers textes et des commandes en ligne. 

**Exemples traditionnels :**
- code source d'un hello world (édition compilation exécution)
- source HTML (édition visualisation)

**Problèmes avec ces exemples :**

- code source : introduit beaucoup de considérations annexes
hors sujet si langage non immédiatement utilisé.
- HTML : nécessité environnement graphique pour visualiser.

**Alternative: **

- fichiers de commandes

# Étape : Commandes, options, paramètres

Interaction par commandes. Quelques exemples (à travailler).

- `date`
- `date -d Friday`  (**options**)
- `date --help` 
- `echo "Hello, world"` (**paramètre**)

pour sortir : 

- `exit`

# Étape : commande `ls`

Pour voir ce qu'il y a dans un répertoire (simplification)

- `ls` pour voir les fichiers présents,
- `ls -l` pour avoir des détails (**option**)
- `ls -l Bibliotheque` (paramètre : chemin d'accès relatif)
- `ls Bibliotheque/M1101-Systeme`

**Trucs :** 

- autocomplétion par TAB.
- historique/édition de la ligne de commande (flèches)

# Étape : afficher ce qu'il y a dans un fichier texte

Différence entre `cat` et `less`.

# Étape : éditer un fichier de commandes

## Frappe d'un petit texte, 

1. Taper un petit texte dans un fichier nommé `essai.sh`

~~~bash
echo -n "Il est "
date +%T
~~~

Éditeur texte à déterminer (`nano`, `vi`, ...)

## Exécution du script

On appelle `script` un fichier qui contient une suite de commandes.

2. Le faire exécuter

~~~
bash essai.sh
~~~

## Modification

Intérêt : on veut faire une réunion en visio avec des gens aux 4
coins de la planète.

Idées : 

1. On ne va calculer les heures de tête, puisqu'on a une commande
qui le fait

~~~
TZ=Asia/Tokyo date +%T
~~~

La commande `date` est précédée par une indication de la TimeZone
(fuseau horaire) à utiliser.

2. On met les commandes dans un fichier, et on n'aura plus besoin
de les relancer


Modèle:

~~~
echo -n "Pour Marcel à Tokyo il est "
TZ=Asia/Tokyo date +%T
~~~



À faire : complétez le script faites afficher les heures pour quelques
personnes que vous connaissez à l'étranger

Indication : la commande `ls /usr/share/zoneinfo/right/` vous montre
les fuseaux connus, par continents/pays.


