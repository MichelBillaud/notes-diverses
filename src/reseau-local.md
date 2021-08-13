% Transmission sur un réseau local
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 31 mai 2020




![](https://i.creativecommons.org/l/by-nc-sa/2.0/fr/88x31.png)

Ce texte fait partie d'une petite [collection de notes](index.html)
mise à disposition selon les termes de la [Licence Creative Commons
Attribution - Pas d’Utilisation Commerciale - Partage dans les Mêmes
Conditions 2.0
France](http://creativecommons.org/licenses/by-nc-sa/2.0/fr/).


# Le problème 

Alice, Bob et Charlie ont des machines connectées à un même réseau local.

Que se passe-t-il lorsque Alice envoie un message message "Hello!" à Bob ?


# Connexion physique des machines

Les trois machines sont connectées par l'intermédiaire de leurs 
cartes réseau (interfaces réseau). 

On suppose ici que c'est un réseau filaire (connexions par câbles). Il
y a donc un boîtier (concentrateur ou commutateur) auquel les 3
machines sont reliées.

# Trames

Le message (La chaîne de caractère "Hello!") est transmis
dans une **trame**.

Une trame, c'est une suite d'octets qui contient

- la "charge utile" (le message),
- l'adresse du destinataire,
- l'adresse de l'expéditeur.

Ici on parle d'**adresses physiques**. Les cartes réseau utilisent
habituellement des "adresses MAC" (Media Access Control) de 6 octets
(48 bits) notée en hexadécimal sous la forme `f4:8e:38:de:f3:d6`.



# Le rôle du boîtier

Les machines du réseau local sont reliées aux prises (ports) d'un
boîtier (techniquement un concentrateur ou un commutateur).

Le rôle du boîtier est de transmettre les trames qu'il reçoit sur un
port vers toutes les machines du réseau local.

**Remarque :** C'est une vision un peu simplifiée, comme toujours la
réalité est un peu plus compliqués :

- il peut y avoir plusieurs boîtiers peuvent
être chaînés entre eux, 
- les commutateurs ne retransmettent que sur un port quand ils 
savent qu'une trame est destinée à une machine reliée à ce port. Voir
annexe "fonctionnement d'un commutateur".


# Émission, transmission et réception d'une trame.


1. Quand l'ordinateur d'Alice veut envoyer un message à celui de Bob :

- il place le message dans une trame, avec
	- la charge utile (une indication du type de message, et son
      contenu),
	- comme adresse de destination, l'adresse MAC de la carte réseau
      de l'ordinateur de Bob,
	- comme adresse source, l'adresse MAC de la carte d'Alice ;
- et il demande à la carte réseau d'envoyer tout ça, sous forme de
  signaux électriques, au boîtier auquel il est relié.

2. Quand le boîtier reçoit cette trame sur un port :

- il la réexpédie sur les autres ports.

3. Quand la carte réseau de l'ordinateur de Bob la reçoit :

- elle constate que la trame lui est destinée (avec le numéro MAC destinataire), on dit alors qu'elle **accepte** la trame.
- elle signale l'arrivée de la trame au système d'exploitation (émission
d'une interruption).
- le système d'exploitation s'en occupe (traitement par le pilote de la carte
réseau).

4. Par contre, la carte réseau de Charlie, en mode normal

- constate que la trame ne lui est pas destinée (numéro MAC différent)
- et l'ignore.

# L'adresse de diffusion

Une adresse spéciale, dite "adresse de diffusion" (*broadcast address*)
sert à envoyer une même trame à toutes les machines. C'est l'adresse MAC
`ff:ff:ff:ff:ff:ff`, qui ne comporte que des 1 en binaire.

En mode normal, une carte réseau qui reçoit une trame, l'accepte donc si
l'adresse de destination est

- sa propre adresse MAC
- ou l'adresse de diffusion.


**Note**: une carte réseau peut être mise dans un mode spécial
(*promiscuous mode*) dans lequel toutes les trames sont
acceptées. C'est ce qui sert à "sniffer le réseau", une occupation
fréquente pendant les travaux pratiques pour comprendre ce qui se passe.

# A qui dois-je écrire ? Protocole de résolution d'adresse.

Pour que ça fonctionne, il faut que 
chaque machine connaisse les adresses MAC de ses interlocuteurs.
C'est difficilement gérable (administrativement) sur un vrai
réseau.

On adopte donc un autre dispositif : chaque machine a un "identifiant"
connu publiquement.  Ici on va dire que c'est son nom, pour
simplifier.

**Exemple** : Quand "alice" veut envoyer un message à "bob", et
qu'elle ne connaît pas déjà son adresse MAC :

- elle fabrique une trame contenant une requête "indiquez moi
  l'adresse MAC de bob svp".
- elle l'envoie à l'adresse de diffusion.

Cette trame est reçue par toutes les machines du réseau local.

- Normalement c'est "bob" qui va répondre à "alice", en indiquant 
sa propre adresse MAC. Il a l'adresse MAC d'Alice (émetteur de la requête)
- Alice peut alors noter cette adresse MAC, et s'en servir pour
  communiquer avec Bob.

Cet échange constitue un **protocole de résolution
d'adresse** (Address Resolution Protocol), un échange de deux messages :

- une **requête** est émise pour demander à quoi correspond à un identifiant
- la **réponse** fournit l'adresse "de bas niveau".


Il existe d'autres possibilités :

- quand une machine se raccorde au réseau, elle se présente ("Hello,
  je suis Dave") par un message envoyé à tous (diffusion) ;
- annonces périodiques pour ceux qui n'étaient pas là ;
- une machine peut servir de **mandataire**, et répondre pour d'autres.



# Annexes

##  Fonctionnement d'un commutateur 

De nos jours, les boîtiers de connexion d'un réseau local sont généralement 
de type "commutateur" (**switch**) :

Un commutateur s'arrange pour réduire le trafic en ne réexpédiant les
trames que sur un seul port, si c'est possible.

### Le problème

Dans un réseau local d'une certaine taille (à partir de quelques
dizaines de poste), comportant plusieurs boîtiers, on souhaite éviter
que toutes les trames soient réexpédiées à toutes les machines.

Deux raisons :

- la **sécurité**, parce qu'une autre machine Eve (pour
  *earsdropping*, laisser traîner les oreilles) pourrait espionner les
  conversations en mettant sa carte en mode "promiscuité".

- le **volume de trafic** : on évite de faire circuler inutilement le
trafic pour réduire la charge des équipements qui ne sont pas
concernés.


### Solution : table d'adresses MAC

Lorsque la machine "Alice", connectée à un certain port `p`
d'un commutateur, envoie une trame sur le réseau local,
cette trame a comme  **adresse d'origine** l'adresse
MAC d'Alice.

Le commutateur apprend donc que ce port `p` permet de joindre
Alice.

Dans le commutateur, une table va mémoriser la correspondance
entre 
les adresses MAC connues et les numéros de ports.

Ensuite, quand le commutateur devra faire passer une trame
dont l'**adresse de destination** est connue, il saura par quel
port l'acheminer.

Ceci réduit la charge du réseau, et limite les possibilités d'espionnage
par écoute du trafic.


### Oublier et réapprendre

Sur un commutateur, les ports ne sont pas affectés de façon définitive.
Avec le dispositif précédent, que se passe-t-il si le technicien réseau 
débranche Alice du port 2 pour la rebrancher sur le port 5 ?

A priori, les trames destinées à Alice continueront d'être expédiées sur
le port 2. Et n'arriveront jamais à destination.

Pour éviter ce problème, le commutateur peut **oublier** la
correspondance entre le port 2 et l'adresse MAC d'Alice, si Alice n'a
rien émis depuis un certain temps (typiquement, 1 ou 2 minutes).
Les données de la table ont une **durée de vie limitée**.

De même, la correspondance sera changée si Alice se met à émettre
depuis un autre port.







