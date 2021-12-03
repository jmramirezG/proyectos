file = open("dia2.txt")

pos = 2*[0]
aim = 0

for line in file:
    line = line.split(' ')
    if ("forward" == line[0]):
        pos[0] += int(line[1])
        pos[1] += aim*int(line[1])
    elif ("up" == line[0]):
        aim -= int(line[1])
    elif ("down" == line[0]):
        aim+= int(line[1])

print(pos[1]*pos[0])