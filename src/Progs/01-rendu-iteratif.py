PIECES = [100, 50, 20, 10, 5, 2, 1]

def rendu_iteratif1(a_rendre):
    solution = []
    for piece in PIECES:
        while a_rendre >= piece:
            solution.append(piece)
            a_rendre = a_rendre - piece
    return solution

def rendu_iteratif(a_rendre):
    solution = []
    for piece in PIECES:
        while a_rendre >= piece:
            solution.append(piece)
            a_rendre = a_rendre - piece
        if a_rendre == 0:
            return solution

        
print ("Tests rendu_iteratif:")
assert rendu_iteratif(68) ==  [50, 10, 5, 2, 1]
assert rendu_iteratif(291) == [100, 100, 50, 20, 20, 1]
print ("Tests rendu_iteratif1:")
assert rendu_iteratif1(68) ==  [50, 10, 5, 2, 1]
assert rendu_iteratif1(291) == [100, 100, 50, 20, 20, 1]
print ("Ok !")
