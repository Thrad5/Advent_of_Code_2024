import sympy as sym

def pt1 (numbers):
    sum = 0
    for numb in numbers:
        x,y = sym.symbols('x,y')
        eq1 = sym.Eq(numb[0]*x+numb[2]*y,numb[4])
        eq2 = sym.Eq(numb[1]*x+numb[3]*y,numb[5])
        result = sym.solve([eq1,eq2],(x,y))
        if type(result[x]) == sym.core.numbers.Integer:
            sum += 3*result[x] + result[y]
    print(f"The answer to part 1 is {sum}")

def main():
    number2 = []
    number = []
    file = open("./input.txt",'r')
    i = 0
    pt_2 = True
    for line in file:
        line = line.split(' ')
        if i < 2:
            number.append(int(line[2][2:-1]))
            number.append(int(line[3][2:-1]))
            i += 1
        elif i == 2:
            if pt_2:
                number.append(int(line[1][2:-1])+10000000000000)
                number.append(int(line[2][2:-1])+10000000000000)
            else:
                number.append(int(line[1][2:-1]))
                number.append(int(line[2][2:-1]))
            i += 1
        elif i == 3:
            number2.append(number)
            number = []
            i = 0
    number2.append(number)
    #print(numbers)
    #print(number2)
    pt1(number2)

main()
