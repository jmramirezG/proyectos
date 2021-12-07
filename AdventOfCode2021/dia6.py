#Por favor, no uséis esto si no queréis que os pete el pc

file = open("dia6.txt")

lista = file.read().strip().split(',')
listaEnteros = [int(x) for x in lista]

data = [listaEnteros[x:x+30] for x in range(0, len(listaEnteros), 30)]

resultado = []

def alg(lista, dia, final = 256):
    for x in range(dia, final):
        if (len(lista) > 300000):
            print("Diviendo en dia " + str(x))
            alg(lista[:150000], x)
            alg(lista[150000:], x)
            return True
        else:
            for element in range(len(lista)):
                if lista[element] == 0:
                    lista[element] = 6
                    lista.append(8)
                else:
                    lista[element] -= 1
        
    resultado.append(len(lista))

"""            
for i in range(len(data)):
    print("Comenzando iteración " + str(i) + "\n")
    for x in range(256):
        print("Dia " + str(x) + "\n")
        for element in range(len(data[i])):
            if data[i][element] == 0:
                data[i][element] = 6
                data[i].append(8)
            else:
                data[i][element]-=1
    resultado += len(data[i])
    data[i].clear()
"""

for lista in data:
    print("Cambio trozo\n")
    alg(lista, 0)

print(sum(resultado))