#
# Totalisation des voix au premier tour de l'élection présidentielle 2022

import csv

nom_fichier = '04-resultats-par-commune.csv'
col_nom     = 26-1
col_nb_voix = 29-1

totaux_voix = {}

print ("= totaux voix premier tour présidentielle 2022")

with open(nom_fichier) as fichier:
    lecteur = csv.reader(fichier)
    numero_ligne = 0
    for ligne in lecteur:
        numero_ligne += 1
        if numero_ligne > 1:
            nom = ligne[col_nom]
            nb_voix = int(ligne[col_nb_voix])
            totaux_voix[nom] = totaux_voix.setdefault(nom, 0) + nb_voix

# affichage final
for (nom, nb_voix) in totaux_voix.items():
    print ('{:10d} {}'.format(nb_voix, nom))
    
