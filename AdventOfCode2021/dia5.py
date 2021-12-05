file = open("dia5.txt")

class Punto:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self): 
        return "[% s, % s]" % (self.x, self.y)

    def __str__(self): 
        return "[% s, % s]" % (self.x, self.y)

validas = []

for line in file:
    line = line.strip().split('->')

    point = []

    for points in line:
        points = points.strip().split(',')
        point.append(Punto(int(points[0]),int(points[1])))


    validas.append([point[0], point[1]])

#print(validas)

sol = [(1000*[0]) for x in range(1000)]

for lista in validas:
    P1, P2 = lista

    #print(P1)
    #print(P2)
    #print("\n")

    if (P1.x == P2.x):
        if P1.y < P2.y:
            sol[P1.x][P1.y]+=1
            while P1.y != P2.y:
                P1.y+=1
                sol[P1.x][P1.y]+=1
        else:
            sol[P1.x][P2.y]+=1
            while P1.y != P2.y:
                P2.y+=1
                sol[P1.x][P2.y]+=1

    elif(P1.y == P2.y):
        if P1.x < P2.x:
            sol[P1.x][P1.y]+=1
            while P1.x != P2.x:
                P1.x+=1
                sol[P1.x][P1.y]+=1
        else:
            sol[P2.x][P1.y]+=1
            while P1.x != P2.x:
                P2.x+=1
                sol[P2.x][P1.y]+=1

    elif (abs(P1.x - P2.x) == abs(P1.y - P2.y)):
        if P1.x < P2.x and P1.y < P2.y:
            sol[P1.x][P1.y]+=1
            while P1.x != P2.x:
                P1.x+=1
                P1.y+=1
                sol[P1.x][P1.y]+=1

        elif P1.x < P2.x and P1.y > P2.y:
            sol[P1.x][P1.y]+=1
            while P1.x != P2.x:
                P1.x+=1
                P1.y-=1
                sol[P1.x][P1.y]+=1

        elif P1.x > P2.x and P1.y < P2.y:
            sol[P1.x][P1.y]+=1
            while P2.x != P1.x:
                P1.x-=1
                P1.y+=1
                sol[P1.x][P1.y]+=1

        else:
            sol[P2.x][P2.y]+=1
            while P2.x != P1.x:
                P2.x+=1
                P2.y+=1
                sol[P2.x][P2.y]+=1


#print(sol)

cont = 0

for row in sol:
    cont = cont + len(row) - row.count(0) - row.count(1)

print(cont)