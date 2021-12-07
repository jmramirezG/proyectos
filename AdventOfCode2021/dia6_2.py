file = open("dia6.txt")

lista = file.read().strip().split(',')
listaEnteros = [int(x) for x in lista]

data = [listaEnteros.count(x) for x in range(9)]

valor0 = 0

listado_dias = [300]

#Cambiar 256 por el número de días que nos pide
for i in range(256):
    valor0 = data[0]
    for num in range(len(data)-1):
        data[num] = data[num+1]
    data[8] = 0
    if valor0 != 0:
        data[6] += valor0
        data[8] = valor0

print(sum(data))