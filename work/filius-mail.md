% Mail DNS - Résolution des noms - Filius
% Michel Billaud (michel.billaud@u-bordeaux.fr,  michel.billaud@laposte.net)
% 3 juillet 2020
 
 
**Objectif**

Expliquer quelques bases sur le Mail avec des manips faisables avec
Filius et ses limitations


# Ce qui est dispo sous FILIUS

- un logiciel client de courrier (SMTP/POP3)
- un serveur de courrier

## Le serveur de courrier

Mail Delivery Agent (MDA) qui

- reçoit le courrier via SMTP pour un domaine
- le stocke dans les boites aux lettres de comptes
- donne accès à ces boites par POP3

Également MTA qui retransmet les mails qui ne lui sont pas destinés.


## Le client de courrier

Mail User Agent (MUA) qui permet

- d'envoyer un mail, en passant par un serveur SMTP (MTA)
- de consulter une boite par POP3.


# Manips

## Manip de base, sur un réseau local

Le but de la manip est de vérifier 

- l'envoi du courrier dans une boite,
- sa récupération par POP.

### Installation, configuration générale

- poste client, avec client messagerie (`pc-alice`, 192.168.1.1)
- serveur messagerie (`mailhost`, 192.168.1.2)
- serveur de noms (`ns`, 192.168.1.3)


Les 3 machines ont pour `192.168.1.3` comme serveur de noms.

Configuration du serveur de noms

| nom            | type | IP          |
| ---            | ---  | ----        |
| pc-alice.work. | A    | 192.168.1.1 |
| mailhost.work. | A    | 192.168.1.2 |
| ns.            | A    | 192.168.1.3 |

### Configuration du serveur de courrier

Sur `mailhost.work`, 

- installez le logiciel "serveur de messagerie"
- configurez-le comme serveur de messagerie pour le domaine `work.`
- démarrez-le.

De ce fait, un message qui arrive sur ce serveur pour `joe@work` sera
censé être livré dans une boite locale au nom de `joe`.  Les autres 
seront réexpédiés.

- créez une boite pour `alice`

Sur le serveur DNS, déclarez que la machine `mailhost.work` est 
l'**échangeur de courrier** (MX = mail exchanger) pour le domaine `work.`
 

| nom   | type | échangeur de courrier |
| ---   | ---  | ---                   |
| work. | MX   | mailhost.work.        |

### Configuration du client de messagerie

Sur `pc-alice`, configurez le client de messagerie pour
qu'il utilise `mailhost.work` comme serveur SMTP et POP3.

Envoyez un mail à `alice@work`.

- vérifiez qu'il est arrivé dans la boite sur `mailhost.work`, 
- sur `pc-alice`, récupérez-le.

## Cas d'erreur


Si ça marche, intéressons-nous aux cas d'erreur :

2. envoyez un mail à `zoe@home`, boite inexistante.

- regardez le journal du serveur,
- sur `pc-alice`, récupérez et analysez la réponse.
   
3. envoyez un mail à `bob@home`, adresse inexistante.

- idem.
   
## Travail 

### Ajouter un serveur de courrier

Maintenant vous allez 

- ajouter un serveur de courrier (`mailhost.home`)
pour le domaine `home.`, de façon à ce qu'`alice@work` puisse
correspondre avec `bob@home`.
- configurer aussi un portable pour `bob`, afin qu'il puisse
faire son courrier.


### Observer les communications


Détaillez les communications DNS, SMTP et POP qui ont lieu quand

- alice envoie un message à bob
- bob relève son courrier
- alice envoie un message à `charlie@work` (compte inexistant
- alice envoie un message à `arthur@camelot` (serveur inexistant)


