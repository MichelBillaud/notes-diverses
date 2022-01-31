#
# NSI 2022, sujet 1
#

def recherche(caractere, mot):
    nb = 0
    for c in mot:
        if c == caractere:
            nb += 1
    return nb


def recherche2(caractere, mot):
    return len([c for c in mot if c == caractere])

def recherche3(caractere, mot):
    return mot.count(caractere)

def recherche4(caractere, mot):
    if len(mot) == 0:
        return 0
    else:
        premier = mot[0]
        suite = mot[1:]
        if premier == caractere:
            return 1 + recherche4(caractere, suite)
        else:
            return recherche4(caractere, suite)
    
def recherche5(caractere, mot):
    if len(mot) == 0:
        return 0
    else:
        nb_occ_suite = recherche5(mot[1:])
        if mot[0] == caractere:
            return 1 + nb_occ_suite
        else:
            return nb_occ_suite


def recherche6 (caractere, mot):
    return 0 if len(mot) == 0 else (
           recherche6(caractere, mot[1:])
              + (1 if caractere == mot[0] else 0))
           
