file = open("dia1.txt")

valor = 4*[0]

contador = 0

for line in file:
    valor = valor[1:] + [int(line)]
    if (valor[0] < valor[3] and valor[0] != 0):   
        contador+=1

print(contador)