
def recherche(caractere, mot, debut = 0):
    if debut == len(mot):
        return 0
    else:
        r = recherche(caractere, mot, debut + 1)
        if caractere == mot[debut]:
            return r + 1
        else:
            return r
        
print (recherche("a", 'abracadabra'))
