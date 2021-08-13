% Adresses IPv4
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 18 juin 2020


# Adresses IPv4.

Les adresses IPv4 sont des nombres codés sur 32 bits, soit 4 octets.

On les exprime habituellement sous forme décimale pointée, chacun des 4 octets
étant traduit en décimal sous forme d'un nombre de 0 à 255.

**Exemple** : adresse IPv4 `10.22.33.44` sous forme décimale pointée,
correspond à  `10*256*256*256 + 22*256*256 + 33*256 + 44` en décimal.



# Préfixe

Un **sous-réseau logique** est un ensemble d'adresses qui "commencent
pareil", par un **préfixe** commun, sur un certain nombre de bits.

Par exemple, les adresses `10.22.33.44` et `10.22.55.66` appartiennent
au même sous-réseau de préfixe `10.22` (sur deux octets, donc de
longueur 16 bits).

Par contre, elles sont sur des sous-réseaux différents si on considère
des préfixes de 24 bits.

Une adresse appartient donc à plusieurs sous-réseaux
correspondant à des préfixes de tailles différentes.


Manière moderne de noter les sous-réseaux : `10.22.0.0/16`. La
première adresse (obtenue en complétant le préfixe par des zéros),
suivi par une barre et le nombre de bits du préfixe.




# Exercices

**Exercice 1**

- Quel est le plus petit sous-réseau qui contient à la fois
 `10.22.33.44` et `10.22.55.66` ?
- Quelles sont sa première et sa dernière addresse ?

**Exercice 2** 

- Montrez que si deux réseaux ont des adresses communes,
alors l'un des deux est inclus dans l'autre.


**Exercice 3**



Soit l'adresse `10.22.33.44` 

- si le préfixe considéré est de 8 bits, à quel sous-réseau appartient-elle ?
- quelles sont les premières et dernières adresses de ce sous-réseau ?
- combien contient-il d'adresses ?
- Mêmes questions pour des préfixes de 16, 20 et 24 bits.


# Masque

Ancienne manière d'indiquer le découpage d'une adresse IPv4 entre
numéro de réseau (préfixe) et numéro d'hôte.  Exemple, dans une commande de
configuration d'interface :

~~~
ifconfig eth0 10.22.33.44 netmask 255.0.0.0 up
~~~

Le **masque** est en notation décimale pointée. La position du préfixe est
indiquée par les bits à 1 du masque (qui sont à gauche).

Exemple, le masque `255.0.0.0` s'écrit en binaire `11111111 00000000
00000000 00000000` et correspond à `/8`, puisque les 8 premiers bits
sont à 1.

La commande ci-dessus peut donc aussi s'écrire (avec profit)

~~~
ifconfig eth0 10.22.33.44/8 up
~~~


Pour le calcul dans l'autre sens : `/28` correspond au masque binaire
`11111111 11111111 11111111 11110000` soit `255.255.255.240`.


| poids | 128 |  64 |  32 |  16 |  8 |  4 |  2 |  1 | 
| -- | -- | -- | -- | -- | -- | -- | -- | -- |
| bits | 1 | 1 | 1 | 1 | 0 | 0| 0 | 0|

128 + 64 + 32 + 16 = 240



**Exercice**

- Calculez les masques correspondant à  `/16`, `/17`, ... `/24`.


