# nsi 2002 - 3


# en utilisant le Duck Typing

class Nombre:
    def __init__(self, valeur):
        self.valeur = valeur

class Binaire:
    def __init__(self, gauche, operateur, droite):
        self.gauche = gauche
        self.operateur = operateur
        self.droite = droite

def infixe(arbre):
    if isinstance(arbre, Nombre):
        return str(arbre.valeur)
    elif isinstance(arbre, Binaire):
        return '(' + infixe(arbre.gauche)\
            + arbre.operateur \
            + infixe(arbre.droite) + ')'
    else:
        raise RuntimeError("Type invalide")

e = Binaire( Binaire(Nombre(3), '*', Binaire(Nombre(8),'+', Nombre(7))),
    '-',  Binaire(Nombre(2), '+', Nombre(1)))

print (e.infixe())
