file = open("dia3.txt")

oxygen = file.read().split('\n')[:-1]

co2 = oxygen.copy()

contador0 = 0
contador1 = 0

for i in range(len(oxygen[0])):
    if (len(oxygen) != 1):
        for numbers in oxygen:
            if (numbers[i] == '0'):
                contador0+=1
            else:
                contador1+=1
        if (contador1>=contador0):
            oxygen = [x for x in oxygen if x[i] == '1']
        else:
            oxygen = [x for x in oxygen if x[i] == '0']
        contador1 = 0
        contador0 = 0

    if (len(co2) != 1):
        for numbers in co2:
            if (numbers[i] == '0'):
                contador0+=1
            else:
                contador1+=1
        if (contador1<contador0):
            co2 = [x for x in co2 if x[i] == '1']
        else:
            co2 = [x for x in co2 if x[i] == '0']
        contador1 = 0
        contador0 = 0


oxygen = int(''.join(oxygen),2)
co2 = int(''.join(co2),2)

print(oxygen*co2)