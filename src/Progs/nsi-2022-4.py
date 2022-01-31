#
# NSI 2002 - 4
#

# def recherche(liste):
#     resultat = []
#     for i in range(1, len(liste)):
#         if liste[i-1] + 1 == liste[i] :
#             resultat.append((liste[i-1], liste[i]))
#     return resultat

def recherche2(liste):
    couples = [ (liste[i-1], liste[i]) for i in range(1, len(liste))]
    return [ (a,b) for (a,b) in couples if a+1 == b ]


def recherche3(liste):
    valeurs = [ liste[i-1] for i in range(1, len(list))
                if liste[i-1]+1 == liste[i] ]
    return [ (v, v+1) for v in valeurs ]


def test(liste):
    print ("recherche(" + str(liste) + ") = " \
           + str(recherche2(liste)))

test([1, 4, 3, 5])
test([1, 4, 5, 3])
test([7, 1, 2, 5, 3, 4])
test([5, 1, 2, 3, 8, -5, -4, 7])

def propager(M, i, j, val):
    if M[i][j] == 0:                                # 1
        return

    M[i][j]=val

    # l'élément en haut fait partie de la composante
    if ((i-1) >= 0 and M[i-1][j] == 1):
        propager(M, i-1, j, val)

    # l'élément en bas fait partie de la composante
    if ((i+1) < len(M) and M[i+1][j] == 1):
        propager(M, i+1, j, val)

    # l'élément à gauche fait partie de la composante
    if ((j-1) >= 0 and M[i][j-1] == 1):
        propager(M, i, j-1, val)

    # l'élément à droite fait partie de la composante
    if ((j+1) < len(M) and M[i][j+1] == 1):
        propager(M, i, j+1, val)

M = [[0,0,1,0],[0,1,0,1],[1,1,1,0],[0,1,1,0]]
propager(M,2,1,3)
print(M)
