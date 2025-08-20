#AoC_day_7

def if_valid(target,operators):
    start = [operators[0]]
    for i in range(1,len(operators)):
        new = []
        for number in start:
            new.append(number + operators[i])
            new.append(number * operators[i])
        start = new
    if (target in start):
        return True
    else:
        return False

def if_valid_pt_2(target,operators):
    start = [operators[0]]
    for i in range(1,len(operators)):
        new = []
        for number in start:
            new.append(number + operators[i])
            new.append(number * operators[i])
            new.append(int(str(number)+str(operators[i])))
        start = new
    if (target in start):
        return True
    else:
        return False

def main():
    file = open('./input.txt','r')
    pt_1_sum = 0
    pt_2_sum = 0
    for line in file:
        line = line.split(': ')
        target = int(line[0])
        operators = list(map(int,line[1].split(' ')))
        if (if_valid(target,operators)):
            pt_1_sum += target
        if(if_valid_pt_2(target,operators)):
            pt_2_sum += target

    print(f"The answer to part 1 is: {pt_1_sum}")
    print(f'The answer to part 2 is: {pt_2_sum}')

main()