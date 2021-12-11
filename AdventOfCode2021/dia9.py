import numpy as np  #@fluque1995


def parse_input():
    with open("dia9.txt", "r") as fin:
        matrix = [list(map(int, line.strip())) for line in fin.readlines()]

    return np.array(matrix)

file = open("dia9.txt")

data = [list(x) for x in file.read().strip().split('\n')]

count = 0

def count_basin(curr_x, curr_y, curr_map_status):
    counter = 1
    curr_map_status[curr_x, curr_y] = True
    if (curr_x - 1 > 0 and not curr_map_status[curr_x - 1, curr_y]):
        counter += count_basin(curr_x - 1, curr_y, curr_map_status)
    if (curr_x + 1 < curr_map_status.shape[0] and
        not curr_map_status[curr_x + 1, curr_y]):
        counter += count_basin(curr_x + 1, curr_y, curr_map_status)
    if (curr_y - 1 > 0 and not curr_map_status[curr_x, curr_y - 1]):
        counter += count_basin(curr_x, curr_y - 1, curr_map_status)
    if (curr_y + 1 < curr_map_status.shape[1] and
        not curr_map_status[curr_x, curr_y + 1]):
        counter += count_basin(curr_x, curr_y + 1, curr_map_status)

    return counter

for i in range(len(data)):
    for j in range(len(data[i])):
        if i == 0:
            if j == 0:
                if data[i][j] < data[i+1][j] and data[i][j] < data[i][j+1]:
                    count += 1 + int(data[i][j])
            elif j == len(data[i])-1:
                if data[i][j] < data[i+1][j] and data[i][j] < data[i][j-1]:
                    count += 1 + int(data[i][j])
            else:
                if data[i][j] < data[i+1][j] and data[i][j] < data[i][j-1] and data[i][j] < data[i][j+1]:
                    count += 1 + int(data[i][j])
        elif i == len(data)-1:
            if j == 0:
                if data[i][j] < data[i-1][j] and data[i][j] < data[i][j+1]:
                    count += 1 + int(data[i][j])
            elif j == len(data[i])-1:
                if data[i][j] < data[i-1][j] and data[i][j] < data[i][j-1]:
                    count += 1 + int(data[i][j])
            else:
                if data[i][j] < data[i-1][j] and data[i][j] < data[i][j-1] and data[i][j] < data[i][j+1]:
                    count += 1 + int(data[i][j])
        elif j == 0:
            if data[i][j] < data[i-1][j] and data[i][j] < data[i+1][j] and data[i][j] < data[i][j+1]:
                count += 1 + int(data[i][j])
        elif j == len(data[i])-1:
            if data[i][j] < data[i-1][j] and data[i][j] < data[i+1][j] and data[i][j] < data[i][j-1]:
                count += 1 + int(data[i][j])
        else:
            if data[i][j] < data[i-1][j] and data[i][j] < data[i+1][j] and data[i][j] < data[i][j-1] and data[i][j] < data[i][j+1]:
                count += 1 + int(data[i][j])

print (count)

original_mat = parse_input()
limits = original_mat == 9
basin_sizes = []

for i in range(limits.shape[0]):
    for j in range(limits.shape[1]):
        if not limits[i, j]:
            basin_sizes.append(count_basin(i, j, limits))


basin_sizes.sort(reverse=True)

print(basin_sizes[0]*basin_sizes[1]*basin_sizes[2])
