import copy

class Walker():
    def __init__(self,pos):
        self.position = pos
        self.facing = "North"
    def inFront(self):
        if self.facing == "North":
            return [self.position[0] - 1, self.position[1]]
        elif self.facing == "East":
            return [self.position[0], self.position[1] + 1]
        elif self.facing == "South":
            return [self.position[0] + 1, self.position[1]]
        else:
            return [self.position[0], self.position[1] - 1]
    def turn(self):
        if self.facing == "North":
            self.facing = "East"
        elif self.facing == "East":
            self.facing = "South"
        elif self.facing == "South":
            self.facing = "West"
        else:
            self.facing = "North"
    def move(self):
        if self.facing == "North":
            self.position = [self.position[0] - 1, self.position[1]]
        elif self.facing == "East":
            self.position = [self.position[0], self.position[1] + 1]
        elif self.facing == "South":
            self.position = [self.position[0] + 1, self.position[1]]
        else:
            self.position = [self.position[0], self.position[1] - 1]

def loopChecker (mover: Walker, maze):
    all_tuples = []
    loc_tuple = (mover.position, mover.facing)
    while((loc_tuple not in all_tuples) and ((0<=mover.position[0]<len(maze)) and (0<=mover.position[1]<len(maze[0])))):
        all_tuples.append(loc_tuple)
        try:
            in_front_of = mover.inFront()
            if(maze[in_front_of[0]][in_front_of[1]] == "#"):
                mover.turn()
            else:
                mover.move()
            #print(f"The Guard's position is {move.position[0]}, {move.position[1]}. The Guard's facing {move.facing}")
            loc_tuple = (mover.position, mover.facing)
        except IndexError:
            break
    mover.move()
    if(mover.position[0]<0 or mover.position[0]>=len(maze)):
        return False
    elif(mover.position[1]<0 or mover.position[1]>=len(maze[0])):
        return False
    if (loc_tuple in all_tuples):
        #print("This is a maze which passes")
        #print(f"The Guard was at {mover.position[0]}, {mover.position[1]} and facing {mover.facing}")
        #for i in maze:
            #print(i)
        return True
    else:
        return False


def main():
    maze = []
    file = open("./test.txt",'r')
    for line in file:
        line = line[:-1]
        line = list(line)
        maze.append(line)
    file.close()
    found = False
    for i in range(len(maze)):
        for j in range(len(maze[i])):
            if maze[i][j] == "^":
                move = Walker([i,j])
                loc = [i,j]
                found = True
                break
        if (found):
            break

    unmodified = copy.deepcopy(maze)
    to_move = Walker(loc)
    loopChecker(to_move,unmodified)

    while ((0<=move.position[0]<len(maze)) and (0<=move.position[1]<len(maze[0]))):
        maze[move.position[0]][move.position[1]] = "X"
        try:
            in_front_of = move.inFront()
            if(maze[in_front_of[0]][in_front_of[1]] == "#"):
                move.turn()
            else:
                move.move()
            #print(f"The Guard's position is {move.position[0]}, {move.position[1]}. The Guard's facing {move.facing}")
        except IndexError:
            break

    num_x = 0
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if maze[i][j] == "X":
                num_x += 1

    print(f"The guard travels {num_x} tiles")

    num_loops = 0
    for i in range(len(maze)):
        for j in range(len(maze[0])):
            if (maze[i][j] == "X") and (unmodified[i][j] != "^"):
                temp = unmodified[i][j]
                unmodified[i][j] = "#"
                test_move = Walker(loc)
                #print(f"Placing block at {i},{j}")
                if (loopChecker(test_move,unmodified)):
                    num_loops += 1
                unmodified[i][j] = temp
    print(f"There are {num_loops} ways to trap the guard in a loop.")

main()


