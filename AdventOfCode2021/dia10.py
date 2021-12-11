file = open("dia10.txt")

data = [list(x) for x in file.read().strip().split('\n')]

values_part1 = {
    ')' : 3,
    ']' : 57,
    '}' : 1197,
    '>' : 25137
}

values_part2 = {
    ')' : 1,
    ']' : 2,
    '}' : 3,
    '>' : 4
}

def median(l):
    half = len(l) // 2
    l.sort()
    if not len(l) % 2:
        return (l[half - 1] + l[half]) / 2.0
    return l[half]

def check_lines(pos, linea, part1):
    caracterActual = linea[pos]
    esperado = []
    if caracterActual == '(':
        esperado.append(')')
        return check_line(pos+1, linea, esperado, part1)
    elif caracterActual == '[':
        esperado.append(']')
        return check_line(pos+1, linea, esperado, part1)
    elif caracterActual == '{':
        esperado.append('}')
        return check_line(pos+1, linea, esperado, part1)
    elif caracterActual == '<':
        esperado.append('>')
        return check_line(pos+1, linea, esperado, part1)

def check_line(pos, linea, expected, part1):
    if pos < len(linea):
        caracterActual = linea[pos]
        if caracterActual == '(':
            expected.append(')')
            return check_line(pos+1, linea, expected, part1)
        elif caracterActual == '[':
            expected.append(']')
            return check_line(pos+1, linea, expected, part1)
        elif caracterActual == '{':
            expected.append('}')
            return check_line(pos+1, linea, expected, part1)
        elif caracterActual == '<':
            expected.append('>')
            return check_line(pos+1, linea, expected, part1)
        elif caracterActual == expected[len(expected)-1]:
            expected.pop()
            return check_line(pos+1, linea, expected, part1)
        else:
            if part1:
                return values_part1[caracterActual]
            else:
                return 0
    else:
        if part1:
            return 0
        else:
            sumaLocal = 0
            expected.reverse()
            for remaining in expected:
                sumaLocal *= 5
                sumaLocal += values_part2[remaining]
            return sumaLocal



suma1 = 0

for line in data:
    suma1 += check_lines(0, line, True)

print(suma1)

suma2 = []

for line in data:
    value = check_lines(0, line, False)
    if value != 0:
        suma2.append(value)

suma2.sort()

print(suma2[len(suma2)//2])