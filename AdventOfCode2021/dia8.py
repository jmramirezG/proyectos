file = open("dia8.txt")

lista = [x.split(' | ') for x in file.read().strip().split('\n')]

listaE, listaS = [],[]

for entrada, salida in lista:
    listaE.append(entrada.split(' '))
    listaS.append(salida.split(' '))

suma = 0

for entrada, salida in zip(listaE, listaS):
    result = {}
    data = []
    valor = len(salida) - 1

    for elem in entrada:
        data.append(set(elem))

    for elem in data:
        if len(elem) == 2:
            result[1] = elem
        if len(elem) == 3:
            result[7] = elem
        if len(elem) == 4:
            result[4] = elem
        if len(elem) == 7:
            result[8] = elem
        
    while(len(result) != 10):
        for elem in data:
            if len(elem) == 5 and len(elem.symmetric_difference(result[7])) == 2:
                result[3] = elem
            elif len(elem) == 6 and len(elem.symmetric_difference(result[4])) == 2:
                result[9] = elem
            elif len(elem) == 6 and len(elem.symmetric_difference(result[4])) == 4 and len(elem.difference(result[7])) == 3:
                result[0] = elem
            elif len(elem) == 6:
                result[6] = elem
            elif len(elem) == 5 and len(result[4].symmetric_difference(elem)) == 3:
                result[5] = elem
            elif len(elem) == 5:
                result[2] = elem

    for element in salida:
        for key, value in zip(result.keys(), result.values()):
            if not len(set(element).symmetric_difference(value)):
                suma += key*(10**valor)
                valor-=1

print(suma)