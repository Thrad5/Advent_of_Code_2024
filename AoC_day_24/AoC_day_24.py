"""
Created on Tue Dec  24 19:38:42 (GMT: +00:00 ) 2024

@author: ram86
"""
import copy

def calculate_z(wires:dict):
    sum = 0
    for key in wires:
        if key[0] == 'z':
            sum += wires[key] << int(key[1:])
    return sum


def pt_1(wires:dict,operation:dict):
    still_2s = True
    #counter = 0
    while(still_2s):
        still_2s = False
        #print(counter,end=',')
        #counter += 1
        for op_key in operation:
            if wires[op_key] == 2:
                if (wires[operation[op_key][1]] == 2 or wires[operation[op_key][2]] == 2):
                    still_2s = True
                else:
                    if operation[op_key][0] == "AND":
                        wires[op_key] = wires[operation[op_key][1]] & wires[operation[op_key][2]]
                    elif operation[op_key][0] == "OR":
                        wires[op_key] = wires[operation[op_key][1]] | wires[operation[op_key][2]]
                    else:
                        wires[op_key] = wires[operation[op_key][1]] ^ wires[operation[op_key][2]]
    '''
    print("\nThe wires currently show")
    for key in wires:
        print(f'{key} -> {wires[key]}')
    print()
    '''
    z_value = calculate_z(wires)
    print(f"The answer to part 1 is {z_value}")
    return z_value

def print_x( wires:dict):
    for key in wires:
        if(key[0] == 'x'):
            print(key)

def pt_2(operations:dict):
    a_n = {}
    b_n = {}
    c_n = {}
    d_n = {}
    z_n = {}
    for op_key in operations:
        if (operations[op_key][1][0] == 'x' or operations[op_key][1][0] == 'y' or operations[op_key][2][0] == 'x' or operations[op_key][2][0] == 'y') and (operations[op_key][0] == "XOR"):
            if op_key == "z00":
                z_n[op_key] = operations[op_key]
            else:
                b_n[op_key] = operations[op_key]
        elif (operations[op_key][1][0] == 'x' or operations[op_key][1][0] == 'y' or operations[op_key][2][0] == 'x' or operations[op_key][2][0] == 'y') and (operations[op_key][0] == "AND"):
            if op_key == "tss":
                a_n[op_key] = operations[op_key]
            else:
                c_n[op_key] = operations[op_key]
        elif operations[op_key][0] == "XOR":
            z_n[op_key] = operations[op_key]
        elif operations[op_key][0] == "AND":
            d_n[op_key] = operations[op_key]
        else:
            a_n[op_key] = operations[op_key]
    print("z_n")
    for z_key in z_n:
        if z_key[0] != 'z':
            print(f"{z_n[z_key][1]} {z_n[z_key][0]} {z_n[z_key][2]} -> {z_key}")
    print("a_n")
    for z_key in a_n:
        if z_key[0] == 'z':
            print(f"{a_n[z_key][1]} {a_n[z_key][0]} {a_n[z_key][2]} -> {z_key}")
    print("b_n")
    for z_key in b_n:
        if z_key[0] == 'z':
            print(f"{b_n[z_key][1]} {b_n[z_key][0]} {b_n[z_key][2]} -> {z_key}")
    print("c_n")
    for z_key in c_n:
        if z_key[0] == 'z':
            print(f"{c_n[z_key][1]} {c_n[z_key][0]} {c_n[z_key][2]} -> {z_key}")
    print("d_n")
    for z_key in d_n:
        if z_key[0] == 'z':
            print(f"{d_n[z_key][1]} {d_n[z_key][0]} {d_n[z_key][2]} -> {z_key}")
    print("z_n back one space")
    print(f"{operations["hgw"][1]} {operations["hgw"][0]} {operations["hgw"][2]} -> hgw")
    print(f"{operations["kvr"][1]} {operations["kvr"][0]} {operations["kvr"][2]} -> kvr")
    print()
    print(f"{operations["wtm"][1]} {operations["wtm"][0]} {operations["wtm"][2]} -> wtm")
    print(f"{operations["wgq"][1]} {operations["wgq"][0]} {operations["wgq"][2]} -> wgq")
    print()
    print(f"{operations["rsm"][1]} {operations["rsm"][0]} {operations["rsm"][2]} -> rsm")
    print(f"{operations["fnq"][1]} {operations["fnq"][0]} {operations["fnq"][2]} -> fnq")
    print("a_n back one space")
    print(f"{operations["kbb"][1]} {operations["kbb"][0]} {operations["kbb"][2]} -> kbb")
    print(f"{operations["gnn"][1]} {operations["gnn"][0]} {operations["gnn"][2]} -> gnn")
    print()
    print(f"{operations["fmh"][1]} {operations["fmh"][0]} {operations["fmh"][2]} -> fmh")
    print(f"{operations["tqs"][1]} {operations["tqs"][0]} {operations["tqs"][2]} -> tqs")
    
    return 0

def main():
    file = open('./input.txt','r')
    wires = {}
    operation = {}
    swapped = False
    x = 0
    y = 0
    for line in file:
        if(line == "\n"):
            swapped = True
            continue
        if swapped:
            line = line.split(" ")
            if line[0] not in wires:
                wires[line[0]] = 2
            if line[2] not in wires:
                wires[line[2]] = 2
            if line[4] not in wires:
                wires[line[4][:-1]] = 2
            operation[line[4][:-1]] = [line[1],line[0],line[2]]
        else:
            line = line.split(":")
            wires[line[0]] = int(line[1])
            if line[0][0] == 'x':
                x += int(line[1]) << int(line[0][1:])
            else:
                y += int(line[1]) << int(line[0][1:])
    sum_1 = pt_1(copy.copy(wires),copy.deepcopy(operation))
    mod_op = copy.deepcopy(operation)
    mod_op["z13"] = ["XOR","hgw","kvr"]
    mod_op["z33"] = ["XOR","wtm","wgq"]
    mod_op["z19"] = ["XOR","rsm","fnq"]
    mod_op["npf"] = ["OR","fmh","tqs"]
    mod_op["cph"] = ["AND","y19","x19"]
    mod_op["hgj"] = ["AND","wgq","wtm"]
    #print_x(wires)
    pt_2(operation)
    sum = pt_1(copy.copy(wires),mod_op)
    print(x + y)
    print(sum - (x+y))
    mod_op["gws"] = ["XOR","x09","y09"]
    mod_op["nnt"] = ["AND","x09","y09"]
    sum = pt_1(copy.copy(wires),mod_op)
    print(x + y)
    print(sum - (x+y))
    return 0

main()

