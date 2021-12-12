matrix = []

with open("dia11.txt","r") as archive:
    for line in archive.readlines():
        line = line.strip()

        to_add = []

        for element in line:
            to_add.append(int(element))

        matrix.append(to_add)


T = 1000

flashes = 0

for day in range(T):

    bool_matrix = [(len(matrix[x])*[False]) for x in range(len(matrix))]

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix[i][j] += 1

    all_nines_checked = False

    while all_nines_checked == False:

        all_nines_checked = True

        for i in range(len(matrix)):
            for j in range(len(matrix[i])):
                if matrix[i][j] > 9:
                    all_nines_checked = False
                    bool_matrix[i][j] = True
                    flashes += 1
                    matrix[i][j] = 0

                    if i == 0:
                        if j == 0:
                            if bool_matrix[i][j+1] == False:
                                matrix[i][j+1] +=1
                            if bool_matrix[i+1][j] == False:
                                matrix[i+1][j] += 1
                            if bool_matrix[i+1][j+1] == False:
                                matrix[i+1][j+1] += 1
                        elif j == len(matrix[i]) - 1:
                            if bool_matrix[i][j-1] == False:
                                matrix[i][j-1] += 1
                            if bool_matrix[i+1][j] == False:
                                matrix[i+1][j] += 1
                            if bool_matrix[i+1][j-1] == False:
                                matrix[i+1][j-1] += 1
                        else:
                            if bool_matrix[i][j-1] == False:
                                matrix[i][j-1] += 1
                            if bool_matrix[i][j+1] == False:
                                matrix[i][j+1] += 1
                            if bool_matrix[i+1][j] == False:
                                matrix[i+1][j] += 1
                            if bool_matrix[i+1][j-1] == False:
                                matrix[i+1][j-1] += 1
                            if bool_matrix[i+1][j+1] == False:
                                matrix[i+1][j+1] += 1

                    elif i == len(matrix)-1:
                        if j == 0:
                            if bool_matrix[i][j+1] == False:
                                matrix[i][j+1] += 1
                            if bool_matrix[i-1][j] == False:
                                matrix[i-1][j] += 1
                            if bool_matrix[i-1][j+1] == False:
                                matrix[i-1][j+1] +=1
                        elif j == len(matrix[i]) - 1:
                            if bool_matrix[i][j-1] == False:
                                matrix[i][j-1] += 1
                            if bool_matrix[i-1][j] == False:
                                matrix[i-1][j] += 1
                            if bool_matrix[i-1][j-1] == False:
                                matrix[i-1][j-1] += 1
                        else:
                            if bool_matrix[i][j-1] == False:
                                matrix[i][j-1] += 1
                            if bool_matrix[i][j+1] == False:
                                matrix[i][j+1] += 1
                            if bool_matrix[i-1][j] == False:
                                matrix[i-1][j] += 1
                            if bool_matrix[i-1][j-1] == False:
                                matrix[i-1][j-1] += 1
                            if bool_matrix[i-1][j+1] == False:
                                matrix[i-1][j+1] += 1
                    
                    else:
                        if j == 0:
                            if bool_matrix[i][j+1] == False:
                                matrix[i][j+1] += 1
                            if bool_matrix[i-1][j] == False:
                                matrix[i-1][j] += 1
                            if bool_matrix[i+1][j] == False:
                                matrix[i+1][j] += 1
                            if bool_matrix[i-1][j+1] == False:
                                matrix[i-1][j+1] += 1
                            if bool_matrix[i+1][j+1] == False:
                                matrix[i+1][j+1] += 1
                        elif j == len(matrix) - 1:
                            if bool_matrix[i][j-1] == False:
                                matrix[i][j-1] += 1
                            if bool_matrix[i-1][j] == False:
                                matrix[i-1][j] += 1
                            if bool_matrix[i+1][j] == False:
                                matrix[i+1][j] += 1
                            if bool_matrix[i-1][j-1] == False:
                                matrix[i-1][j-1] += 1
                            if bool_matrix[i+1][j-1] == False:
                                matrix[i+1][j-1] += 1
                        else:
                            if bool_matrix[i][j+1] == False:
                                matrix[i][j+1] += 1
                            if bool_matrix[i][j-1] == False:
                                matrix[i][j-1] += 1
                            if bool_matrix[i+1][j] == False:
                                matrix[i+1][j] += 1
                            if bool_matrix[i-1][j] == False:
                                matrix[i-1][j] += 1
                            if bool_matrix[i-1][j-1] == False:
                                matrix[i-1][j-1] += 1
                            if bool_matrix[i-1][j+1] == False:
                                matrix[i-1][j+1] += 1
                            if bool_matrix[i+1][j-1] == False:
                                matrix[i+1][j-1] += 1
                            if bool_matrix[i+1][j+1] == False:
                                matrix[i+1][j+1] += 1
    diaFlash = True                            
    for elem in bool_matrix:
        if elem.count(False) != 0:
            diaFlash = False

    if diaFlash:
        print(day+1)
        break

print(flashes)
print(matrix)