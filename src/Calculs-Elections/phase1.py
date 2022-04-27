#
# Phase 1 : vérifier qu'on arrive a extraire les noms et
# nombre de voix obtenus

import csv

nom_fichier = '04-resultats-par-commune.csv'
col_nom     = 26-1
col_nb_voix = 29-1

limite_ligne = 5

with open(nom_fichier) as fichier:
    lecteur = csv.reader(fichier)
    numero_ligne = 0
    for ligne in lecteur:
        numero_ligne += 1
        if numero_ligne > limite_ligne:
            break
        if numero_ligne > 1:
            print ("nom =", ligne[col_nom], "voix =", ligne[col_nb_voix])
