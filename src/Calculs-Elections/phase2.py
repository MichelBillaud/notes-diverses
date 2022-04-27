#
# Phase 2 : extraire les noms et nombre de voix obtenus
# vérifier le cumul

import csv

nom_fichier = '04-resultats-par-commune.csv'
col_nom     = 26-1
col_nb_voix = 29-1

limite_ligne = 20
totaux_voix = {}

with open(nom_fichier) as fichier:
    lecteur = csv.reader(fichier)
    numero_ligne = 0
    for ligne in lecteur:
        numero_ligne += 1
        if numero_ligne > limite_ligne:
            break
        if numero_ligne > 1:
            nom = ligne[col_nom]
            nb_voix = int(ligne[col_nb_voix])
            print ("nom =", nom, "voix =", nb_voix)
            totaux_voix[nom] = totaux_voix.setdefault(nom, 0) + nb_voix
            print ("=", totaux_voix)
print ("totaux", totaux_voix)
