#
# NSI 05
#

# pour n entier strictement positif

def conv_bin(n):
    bits = []
    while n != 0:
        bit = n % 2
        n = n // 2
        bits.append(bit)
    bits.reverse()
    return (bits, len(bits))
        

print ("Tests :")
assert conv_bin(1) ==  ([1], 1)
assert conv_bin(2) ==  ([1, 0], 2)
assert conv_bin(9) ==  ([1, 0, 0, 1], 4)
assert conv_bin(10) == ([1, 0, 1, 0], 4)
print("Ok!")

def tri_bulles(T):
    n = len(T)
    for i in range(n-1, 1, -1):  #1
        for j in range(i):
            if T[j] > T[j+1]:    #2
                temp = T[j]      #3
                T[j] = T[j+1]    #4
                T[j+1] = temp
    return T


print("Test tri")
assert tri_bulles([4, 1, 5, 2, 3]) ==  [1, 2, 3, 4, 5]
print("Ok")
