"""
Created on Tue Dec  10 07:51:44 (GMT: +00:00 ) 2024

@author: ram86
"""
class Pathfinder():
    def __init__(self,pos:list[int],value,origin):
        self.position = pos
        self.height = value
        self.origin = origin
        self.complete = False
        self.to_delete = False

def allDone(paths:list[Pathfinder]):
    for path in paths:
        if not path.complete:
            return False
    return True

def neigboursContinuing(path:Pathfinder,size,ma):
    neigbours = [0,0,0,0]
    if (path.position[0]-1 >=0):
        if (path.height + 1 == int(ma[path.position[0] - 1][path.position[1]])):
            neigbours[0] = 1
    if path.position[1] + 1 < size[1]:
        if (path.height + 1 == int(ma[path.position[0]][path.position[1] + 1])):
            neigbours[1] = 1
    if (path.position[0]+1 < size[0]):
        if (path.height + 1 == int(ma[path.position[0] + 1][path.position[1]])):
            neigbours[2] = 1
    if path.position[1] - 1 >= 0:
        if (path.height + 1 == int(ma[path.position[0]][path.position[1] - 1])):
            neigbours[3] = 1
    return neigbours

def noDeletes(paths:list[Pathfinder]):
    for path in paths:
        if path.to_delete:
            return True
    return False

def pt_1(mp):
    paths: list[Pathfinder] = []
    for i in range(len(mp)):
        for j in range(len(mp[0])):
            if mp[i][j] == '0':
                paths.append(Pathfinder([i,j],0,[i,j]))
    size = [len(mp),len(mp[0])]
    while not allDone(paths):
        #print(f"There are currently {len(paths)} active paths")
        for pathf in paths:
            if not pathf.complete:
                neigh = neigboursContinuing(pathf,size,mp)
                if sum(neigh) == 0 and pathf.height != 9:
                    #print(f"The walker being deleted has value {pathf.height}")
                    pathf.to_delete = True
                elif sum(neigh) == 0 and pathf.height == 9:
                    pathf.complete = True
                elif sum(neigh) == 1:
                    if neigh[0] == 1:
                        pathf.position[0] = pathf.position[0] - 1
                    elif neigh[1] == 1:
                        pathf.position[1] = pathf.position[1] + 1
                    elif neigh[2] == 1:
                        pathf.position[0] = pathf.position[0] + 1
                    else:
                        pathf.position[1] = pathf.position[1] - 1
                    pathf.height += 1
                elif sum(neigh) == 2:
                    if neigh[0] == 1:
                        pathf.position[0] = pathf.position[0] - 1
                        pathf.height += 1
                        if neigh[1] == 1:
                            paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1] + 1],pathf.height,pathf.origin))
                        elif neigh[2] == 1:
                            paths.append(Pathfinder([pathf.position[0] + 2,pathf.position[1]],pathf.height,pathf.origin))
                        else:
                            paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1] - 1],pathf.height,pathf.origin))
                    elif neigh[1] == 1:
                        pathf.position[1] = pathf.position[1] + 1
                        pathf.height += 1
                        if neigh[2] == 1:
                            paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1] - 1],pathf.height,pathf.origin))
                        else:
                            paths.append(Pathfinder([pathf.position[0], pathf.position[1] - 2],pathf.height,pathf.origin))
                    elif neigh[2] == 1:
                        pathf.position[0] = pathf.position [0] + 1
                        pathf.height += 1
                        paths.append(Pathfinder([pathf.position[0]-1,pathf.position[1]-1],pathf.height,pathf.origin))
                    else:
                        print("Something has gone wrong")
                        return 1
                elif sum(neigh) == 3:
                    if neigh[0] == 1:
                        pathf.position[0] = pathf.position[0] - 1
                        pathf.height += 1
                        if neigh[1] == 1:
                            paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1] + 1],pathf.height,pathf.origin))
                            if neigh[2] == 1:
                                paths.append(Pathfinder([pathf.position[0] + 2,pathf.position[1]],pathf.height,pathf.origin))
                            else:
                                paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1]-1],pathf.height,pathf.origin))
                        elif neigh[2] == 1:
                            paths.append(Pathfinder([pathf.position[0] + 2,pathf.position[1]],pathf.height,pathf.origin))
                            paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1] - 1],pathf.height,pathf.origin))
                        else:
                            print("Something has gone wrong..")
                            return 1
                    else:
                        pathf.position[1] = pathf.position[1] + 1
                        pathf.height += 1
                        paths.append(Pathfinder([pathf.position[0] + 1,pathf.position[1]-1],pathf.height,pathf.origin))
                        paths.append(Pathfinder([pathf.position[0],pathf.position[1]-2],pathf.height,pathf.origin))
        
        while noDeletes(paths):
            for pathg in paths:
                if pathg.to_delete:
                    paths.remove(pathg)
                    break
    unique_origins = []
    number_of = []
    for po in paths:
        if len(unique_origins) == 0:
            unique_origins.append(po.origin)
            number_of.append(1)
        else:
            if po.origin not in unique_origins:
                unique_origins.append(po.origin)
                number_of.append(1)
            else:
                index = unique_origins.index(po.origin)
                number_of[index] += 1
    origin_pos_pairs = []
    for path in paths:
        if [path.position,path.origin] not in origin_pos_pairs:
            origin_pos_pairs.append([path.position,path.origin])

    
    print(f"The Answer to part one is {len(origin_pos_pairs)}")
    print(f"The answer to part 2 is {len(paths)}")

    return 0


def main():
    file = open('test.txt','r')
    mount_map = []
    for line in file:
        line = list(line[:-1])
        mount_map.append(line)
    pt_1(mount_map)
    
main()
