"""
Created on Sun Dec  08 14:03:33 (GMT: +00:00 ) 2024

@author: ram86
"""


def pt_1(size,pylons):
    anti_nodes = []
    for key in pylons:
        for i in range(len(pylons[key])):
            for j in range(i):
                dist = [pylons[key][i][0]-pylons[key][j][0],pylons[key][i][1]-pylons[key][j][1]]
                an = [pylons[key][i][0]+dist[0],pylons[key][i][1]+dist[1]]
                if (not (an[0]<0 or an[0]>=size[0] or an[1]<0 or an[1]>=size[1])) and (not (an in anti_nodes)):
                    anti_nodes.append(an)
                an = [pylons[key][j][0]-dist[0],pylons[key][j][1]-dist[1]]
                if (not (an[0]<0 or an[0]>=size[0] or an[1]<0 or an[1]>=size[1])) and (not (an  in anti_nodes)):
                    anti_nodes.append(an)
    print(f"There are {len(anti_nodes)} antinodes in the map.")

    return 0

def pt_2(size:list,pylons:dict,anti_nodes:list):
    for key in pylons:
        for i in range(len(pylons[key])):
            for j in range(i):
                dist = [pylons[key][i][0]-pylons[key][j][0],pylons[key][i][1]-pylons[key][j][1]]
                an = [pylons[key][i][0]+dist[0],pylons[key][i][1]+dist[1]]
                while (not (an[0]<0 or an[0]>=size[0] or an[1]<0 or an[1]>=size[1])):
                    if not (an in anti_nodes):
                        anti_nodes.append(an)
                    an =[an[0]+dist[0],an[1]+dist[1]]
                an = [pylons[key][i][0]-dist[0],pylons[key][i][1]-dist[1]]
                while (not (an[0]<0 or an[0]>=size[0] or an[1]<0 or an[1]>=size[1])):
                    if not (an in anti_nodes):
                        anti_nodes.append(an)
                    an =[an[0]-dist[0],an[1]-dist[1]]
    print(f"There are {len(anti_nodes)} antinodes in the map.")
                
    return 0

def main():
    file = open('input.txt','r')
    grid = []
    for line in file:
        grid.append(list(line[:-1]))
    size = [len(grid),len(grid[0])]
    pylons = {}
    anti_nodes = []
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] in pylons:
                pylons[grid[i][j]].append([i,j])
                anti_nodes.append([i,j])
            elif grid[i][j] != '.':
                pylons[grid[i][j]] = [[i,j]]
                anti_nodes.append([i,j])
    pt_1(size,pylons)
    pt_2(size,pylons,anti_nodes)
main()
