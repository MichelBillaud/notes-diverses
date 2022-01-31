# nsi 2002 - 3

class Arbre:
    def est_nombre(self):
        return False
    def est_binaire(self):
        return False

class Nombre(Arbre):
    def __init__(self, valeur):
        self.valeur = valeur
    def est_nombre(self):
        return True
    def infixe(self):
        return str(self.valeur)

class Binaire(Arbre):
    def __init__(self, gauche, operateur, droite):
        self.gauche = gauche
        self.operateur = operateur
        self.droite = droite
    def est_binaire(self):
        return True
    def infixe(self):
        return '(' + self.gauche.infixe() \
               + self.operateur \
               + self.droite.infixe() + ')'


e = Binaire( Binaire(Nombre(3), '*', Binaire(Nombre(8),'+', Nombre(7))),
    '-',  Binaire(Nombre(2), '+', Nombre(1)))

print (e.infixe())
