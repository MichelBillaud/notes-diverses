% Notes ipv6
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 24 juin 2020
 


# Adresses IPv6, notation

## Adresses

Les adresses IPV6 sont sur 128 bits.  On les
note par une écriture hexadécimale, par groupes de 16 bits (soit 2
octets = 4 chiffres hexadécimaux). Exemple

~~~
2001:0db8:0000:85a3:0000:0000:ac1f:8001
~~~

que l'on raccourcit en

1. supprimant les zéros non significatifs
2. remplaçant éventuellement une suite de groupes de 0 par "::"

~~~
forme longue: 2001:0db8:0000:85a3:0000:0000:ac1f:8001
1          -> 2001: db8:   0:85a3:   0:   0:ac1f:8001
2          -> 2001: db8:   0:85a3:         :ac1f:8001

forme courte:  2001:db8:0:85a3::ac1f:8001
~~~~

Rappel : pour les adresses IPv4 (32 bits) on utilise la
notation décimale pointée, exemple `172.17.94.33`, chaque octet étant
codé par sa valeur en décimal.


## Préfixes 

Un **préfixe** sert à identifier un "sous-réseau", un ensemble d'adresses
"qui commencent pareil" (bits de poids fort). Il indique donc les bits
communs à ces adresses.

On le note par la première adresse, suivie par un "/" et la longueur
du préfixe. Par exemple, le préfixe `2001:db8:1f89::/48` représente
l’ensemble des adresses qui commence à `2001:db8:1f89:0:0:0:0:0` et
finit à `2001:db8:1f89:ffff:ffff:ffff:ffff:ffff`.


**Rappel** : on retrouve ici la notation *Classless Inter-Domain
Routing* (CIDR), présentée en 1993 dans la RFC 1518 pour IPv4. Exemple
`172.17.94.0/24` représente les adresses de `192.16.94.0` à
`192.16.94.255`, ce qui correspond à un "masque de sous-réseau" de
`255.255.255.0`.

## Types d'adresses

| Préfixe | Type |	Description |          
| --------| ------------|----------|
| `::/8`  | 	Adresses réservées | |
| `2000::/3`  | 	Adresses unicast routables sur Internet | |
| `fc00::/7`  | 	Adresses locales uniques | |
| `fe80::/10`  | 	Adresses locales lien 	| Envoi individuel sur liaison locale | 
| `ff00::/8`  | 	Adresses multicast 	| Diffusion groupée.   |

### Adresses réservées `0::/8`

Ont le premier octet à 0 (donc le premier groupe de `0000` à `00FF`).  Parmi les adresses réservées :

- l'**adresse non spécifiée** `::/128` (qui ne contient que des zeros) analogue à `0.0.0.0`
- l'**adresse de loopback** `::1/128`, semblable à `127.0.0.1`.

### Adresses unicast globales `2000::/3`

Ce sont les adresses "normales", attribuées par des fournisseurs d'accès,
routables sur internet et destinées à la communication
point à point (**unicast**)

- les adresses `2001::/32` et `2002::/16` sont utilisées pour des
  mécanismes de compatibilité avec IPv4
- les adresses `2001:db8::/32` sont réservées à la documentation et
  les essais.

Une adresse unicast comporte trois parties

- un **préfixe de routage global**, attribué par votre fournisseur
d'accès (de 48 à 64 bits), et qui lui permet d'acheminer les paquets
qui vous sont destinés vers les routeurs de votre réseau physique.
- un **identificateur de sous-réseau**, qui vous permet d'aiguiller les
transferts entre les parties de votre réseau.
- un **identificateur d'interface**.

### Adresses link-local

Au démarrage, les machines attribuent elles-mêmes (SLAAC = IPv6
Stateless **Address Autoconfiguration**) à leur(s) interface(s) une
adresse IPv6 dite "local-link" pour communiquer de suite avec les
autres machines du même réseau local. Elles ne sont pas routées vers
d'autres réseaux physiques.

Ces adresses sont construites en combinant le
préfixe `fe80::/10` et un identifiant d'interface.
L'identifiant est souvent calculé à partir de 
l'adresse MAC de la carte réseau, exemple :

~~~ 
adresse mac             :  f4:8e:38:de:ab:7a 
adresse ipv6 local-link :  fe80::f68e:38ff:fede:ab7a/64 
~~~

on y retrouve l'adresse MAC, à un bit inversé près.  L'adresse IPv6
étant prévisible, il est recommandé d'utiliser un identifiant
"aléatoire" calculé par un autre algorithme (rfc7217), et un test pour
le cas très improbable où l'adresse aurait déjà été utilisée. Cette
recommandation n'est pas toujours suivie.


### Multicast

Qu'est-ce que c'est : la possibilité d'envoyer un même message à
plusieurs machines, qui ne sont pas forcément sur le même réseau
physique (contrairement au broadcast). Ces machines forment un groupe,
identifié par un numéro IP spécifique.

C'est ce qui est utilisé par exemple pour la réception de la
télévision par IP dans un réseau domestique. Si vous regardez la même
chaîne depuis plusieurs appareils, votre fournisseur ne transmet les
flux qu'en un exemplaire à votre routeur domestique.


Les machines qui rejoignent (s'abonnent) à un groupe multicast
préviennent leur routeur qu'il doit leur faire parvenir les messages
du groupe, si il les voit passer (et récursivement, ...)

Sur le réseau local, les messages envoyés en multicast sont transmis
dans des trames dont l'adresse MAC de destination contient
`33:33:xx:xx:xx:xx`, où les x sont les 32 bits de poids faible du
numéro de groupe multicast IPV6.

Quand un processus d'une machine s'abonne à un groupe, elle configure
sa carte réseau pour que l'arrivée d'une telle trame soit détectée, et
signalée au système d'exploitation, qui transmettra au processus.




**Pour IPv4**, les adresses multicast vont de `224.0.0.0` à
`239.255.255.255`, ce qui fait 28 bits de "numéro de groupe multicast".  Les
messages sont envoyées à l'adresse MAC `00:01:50:yy:yy:yy` où les yy
contiennent, pour de sordides raisons historiques, les 23 bits de
poids faible du numéro de groupe (le bit le plus à gauche est forcé à 0).



### Network discovery protocol

Une fois que la machine qui démarre s'est attribuée une adresse "local
link", elle s'en sert pour envoyer une "requête de
sollicitation des routeurs" au **groupe multicast** des routeurs.

Normalement, un routeur présent sur le réseau local répond en indiquant
l'adresse IPv6 que la machine peut utiliser et des informations
de configuration (c'est l'équivalent d'un DHCP).



### Adresses locales uniques,


