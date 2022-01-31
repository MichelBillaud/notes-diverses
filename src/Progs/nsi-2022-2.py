#
# NSI 2022, sujet 2
#

def moyenne(liste):
    somme_produits = 0
    somme_coefficients = 0
    for (note, coefficient) in liste:
        somme_produits += note * coefficient
        somme_coefficients += coefficient
    return somme_produits / somme_coefficients
        

def moyenne2(liste):
    somme_produits     = sum( note * coefficient for (note, coefficient) in liste)
    somme_coefficients = sum(coefficient         for (note, coefficient) in liste)
    return somme_produits / somme_coefficients
    

print (moyenne([(15,2), (9,1), (12,3)]))
print (moyenne2([(15,2), (9,1), (12,3)]))


def pascal(n):
	C = [[1]]
	for k in range(1, n + 1):                            #1
		Ck = [1]                                     #2
		for i in range(1, k):
			Ck.append(C[k-1][i-1] + C[k-1][i] )  #3
		Ck.append(1)                                 #4
		C.append(Ck)
	return C

print(pascal(4))
