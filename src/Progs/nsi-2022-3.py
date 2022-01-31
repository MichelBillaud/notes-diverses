# nsi 2002 - 3

def delta(liste):
    resultat = []
    derniere = 0
    for donnee in liste:
       resultat.append(donnee - derniere)
       derniere = donnee
    return resultat


def delta2(liste):
    resultat = [ liste[0] ]
    for i in range(1, len(liste)):
        resultat.append(liste[i] - liste[i-1])
    return resultat

print (delta2([1000, 800, 802, 1000, 1003]))


class Noeud:
    def __init__(self, g, v, d):
        self.gauche = g
        self.valeur = v
        self.droit = d
        
    def __str_(self):
        return str(self.valeur)
    
    def est_une_feuille(self):
        '''Renvoie True si et seulement si le noeud est une feuille'''
        return self.gauche is None and self.droit is None

##
##def expression_infixe(n):         # le paramètre est un noeud
##    if n.est_une_feuille() :
##        return str(n.valeur)
##    else:
##        return "(" + expression_infixe(n.gauche) + n.valeur \
##               + expression_infixe(n.droit) + ")"
##    

def expression_infixe(e):
    s = ''                                   #1
    if e.gauche is not None:
        s = s + expression_infixe(e.gauche)  #2
    s = s + str(e.valeur)                    #3
    if e.droit is not None:                  #4
        s = s + expression_infixe(e.droit)   #5
    if e.est_une_feuille():                  #6
        return s
    return '('+ s +')'



e = Noeud(Noeud(Noeud(None, 3, None), '*', Noeud(Noeud(None, 8, None),
'+', Noeud(None, 7, None))), '-', Noeud(Noeud(None, 2, None), '+',
Noeud(None, 1, None)))

print (expression_infixe(e))
