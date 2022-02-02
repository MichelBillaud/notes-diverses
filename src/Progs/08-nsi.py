# nsi 8

def recherche(element, tableau):
    for i in range(len(tableau)):

        if tableau[i] == element:
            return i
    return -1

print ("Tests")
assert recherche(1, [2, 3, 4])       == -1
assert recherche(1, [10, 12, 1, 56]) == 2
assert recherche(50, [1, 50, 1])     == 1
assert recherche(15, [8, 9, 10, 15]) == 3
print ("OK")

       
def insere(a, tab):
    l = list(tab) #l contient les mêmes éléments que tab
    l.append(a)
    i = len(l) - 2                # 1
    while a < l[i] and i >= 0:    # 2
        l[i+1] = l[i]             # 3
        l[i]   = a                  
        i = i - 1                 # 4
    return l

print ("tests insertion")
assert insere(3,[1,2,4,5]) == [1, 2, 3, 4, 5]
assert insere(10,[1,2,7,12,14,25]), [1, 2, 7, 10, 12, 14, 25]
assert insere(1,[2,3,4]) == [1, 2, 3, 4]
print ("test ok");
