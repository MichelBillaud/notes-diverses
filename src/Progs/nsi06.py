# nsi 2022 - 6


def maxi(tab):
    valeur_maxi = tab[0]
    indice_maxi = 0
    for i in range(1, len(tab)):
        if tab[i] > valeur_maxi:
            valeur_maxi = tab[i]
            indice_maxi = i
    return (valeur_maxi, indice_maxi)


def verifier_maxi(tab, attendu):
    print ("# appel maxi(" + str(tab) + ")")
    print ("- résultat attendu = " + str(attendu))
    print ("- resultat obtenu  = " + str(maxi(tab)))

verifier_maxi([1,5,6,9,1,2,3,7,9,8], (9,3))
verifier_maxi([5, 1, 2, 3], (5, 0))   #cas du premier
verifier_maxi([5, 1, 2, 5], (5, 0))   #cas du premier
verifier_maxi([11, 22, 33], (33, 2))  #cas du dernier 

def recherche(gene, seq_adn):
    n = len(seq_adn)
    g = len(gene)
    i = 0                                  # 1
    trouve = False
    while i < n-g+1 and trouve == False :        # 2
        j = 0
        while j < g and gene[j] == seq_adn[i+j]:
            j += 1                              # 3
        if j == g:
            trouve = True
        i += 1                              # 4
    return trouve

recherche("AATC", "GTACAAATCTTGCC")
recherche("AGTC", "GTACAAATCTTGCC")

