file = open("dia7.txt")

lista = file.read().strip().split(',')
listaEnteros = [int(x) for x in lista]

maximo = 0
for elem in listaEnteros:
    if elem > maximo:
        maximo = elem


optima = float('inf')
pos = 0

sumaLocal = 0

for i in range(maximo):
    for elem in listaEnteros:
        n = abs(elem-i)
        sumaLocal += (n*(n+1))/2
    if (sumaLocal < optima):
        optima = sumaLocal
        pos = i
    sumaLocal = 0

print(optima)
print(pos)