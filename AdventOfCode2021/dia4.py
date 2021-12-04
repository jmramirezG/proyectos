def haGanado(matriz):
    for row in matriz:
        if (sum(list(map(int,row))) == -5):
            return True

    if (matriz[0][0] == matriz[1][0] == matriz[2][0] == matriz[3][0] == matriz[4][0] == '-1'):
        return True
    
    if (matriz[0][1] == matriz[1][1] == matriz[2][1] == matriz[3][1] == matriz[4][1] == '-1'):
        return True
    
    if (matriz[0][2] == matriz[1][2] == matriz[2][2] == matriz[3][2] == matriz[4][2] == '-1'):
        return True

    if (matriz[0][3] == matriz[1][3] == matriz[2][3] == matriz[3][3] == matriz[4][3] == '-1'):
        return True
    
    if (matriz[0][4] == matriz[1][4] == matriz[2][4] == matriz[3][4] == matriz[4][4] == '-1'):
        return True

    return False


file = open("dia4.txt")

numeros = file.readline().strip().split(',')

matrices = [col.strip('').split(' ') for col in [ row for row in file.read().strip().split('\n') if row] if col]

listaMat = []
aux = []
contador = 0

for row in matrices:
    if (row.count('') > 0):
        row.remove('')
        if (row.count('') > 0):
            row.remove('')
            if (row.count('') > 0):
                row.remove('')

    aux.append(row)

    if (len(aux) == 5):
        listaMat.append(aux)
        aux = []


ganadora = []
numeroG = 0

fin = True

for numero in numeros:
    fin = True
    for x in range(len(listaMat)):
        if (haGanado(listaMat[x]) == False):
            for y in range(len(listaMat[x])):
                for z in range(len(listaMat[x][y])):
                    if (numero == listaMat[x][y][z]):
                        listaMat[x][y][z] = '-1'
            if (haGanado(listaMat[x])):
                ganadora = listaMat[x]
                numeroG = int(numero)
    for x in range(len(listaMat)):
        if (haGanado(listaMat[x]) == False):
            fin = False
        if (fin == True):
            break;

suma = 0

for row in ganadora:
    suma += list(map(int,row)).count(-1)
    suma += sum(list(map(int,row)))

print(suma*numeroG)
