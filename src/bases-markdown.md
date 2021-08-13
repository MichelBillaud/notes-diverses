% Bases Markdown
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 12 juin 2020


![](https://i.creativecommons.org/l/by-nc-sa/2.0/fr/88x31.png)
Ce texte fait partie d'une petite [collection de notes](index.html)
mise à disposition selon les termes de la 
[Licence Creative Commons
Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes
Conditions 2.0
France](http://creativecommons.org/licenses/by-nc-sa/2.0/fr/).


# Structure d'un document

Un document Markdown commence par une entête de 3 lignes, 
suivie par un texte structuré.

## Entête du document

Les lignes de l'entête commencent par le caractère "pourcent", et 
donnent le titre, l'auteur et la date.

**Exemple**

~~~markdown
% Exercices de programmation
% Alan Smithee
% 1er Avril 2021
~~~


## Titraille

Les lignes de titres commencent par des dièses `#`, dont le nombre indique
le niveau.

**Exemple :**

~~~markdown
# Structure d'un document

Un document Markdown commence par une entête de 3 lignes, 
suivie par un texte structuré.

## Entête du document

Les lignes de l'entête commencent par le caractère "pourcent", et 
donnent le titre, l'auteur et la date.

**Exemple**
....
~~~


# Décoration des caractères

**Si on tape :**

~~~markdown
Les textes "décorés" sont entourés
- par des étoiles pour les *italiques*,
- par des étoiles pour les **caractères gras**,
- par des "backquotes" pour du `code informatique`.
~~~

**On voit :**

Les textes "décorés" sont entourés
- par des étoiles pour les *italiques*,
- par des étoiles pour les **caractères gras**,
- par des "backquotes" pour du `code informatique`.

**Remarque**: pour afficher ces caractères spéciaux tels-quels, les
précéder d'un *antislash* `\`.


# Listes

## Listes à puces

Chaque élément commence par un tiret. Sous-listes décalées.

~~~markdown
- France
   - Vin
   - Fromage
- Italie
   - Pizza
   - Scooter
~~~

Apparence : 

- France
     - Vin
	 - Fromage
- Italie
     - Pizza
	 - Scooter

## Listes numérotée

~~~
1. FORTRAN
2. LISP
3. COBOL
~~~

**Apparence :**

1. FORTRAN
2. LISP
3. COBOL

# Blocs de code

Un bloc de code est encadré par des lignes "`~~~`".
Le nom du langage permet la colorisation des mots-clés.

**Par exemple :**
```markdown
~~~java
int en_couleur () {
   return 1;
}
~~~
```

apparaît sous la forme :

~~~java
int en_couleur () {
   return 1;
}
~~~

**Remarque.** On peut aussi utiliser la marque "\`\`\`", le bloc pourra alors
contenir l'autre marque.


# Liens hypertexte, pour en savoir plus.

~~~markdown
Lisez la [documentation](https://pandoc.org/MANUAL.html)
~~~

Lisez la [documentation](https://pandoc.org/MANUAL.html)

