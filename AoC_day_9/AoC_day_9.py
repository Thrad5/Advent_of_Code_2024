"""
Created on Mon Dec  09 18:13:06 (GMT: +00:00 ) 2024

@author: ram86
"""
import copy
def checksum(f):
    su = 0
    for i in range(len(f)):
        if f[i] == '.':
            continue
        else:
            su += i*int(f[i])
    return su

def pt_1(expanded):
    rev_id = len(expanded) - 1
    while expanded[rev_id] == '.':
        rev_id -= 1
    for_id = 0
    while for_id < rev_id:
        if expanded[for_id] == '.':
            expanded[for_id] = expanded[rev_id]
            expanded[rev_id] = '.'
            while expanded[rev_id] == '.':
                rev_id -= 1
        for_id += 1
    pt_1_sum = checksum(expanded)
    print(f"The answer to part one is {pt_1_sum}")
    return 0

def pt_2(expanded,gap_locs,file_locs):
    #print(expanded)
    rev_file_locs = []
    rev_id = len(file_locs) - 1
    while rev_id >=0:
        rev_file_locs.append(file_locs[rev_id])
        rev_id -= 1
    for file in rev_file_locs:
        change = False
        for i in range(len(gap_locs)):
            '''print(f'\nTesting {file[2]}')
            print(f"The current gap is at position {gap_locs[i][1]} and is {gap_locs[i][0]} long.")
            print(f"The result of gaps_locs[i][1]<file[1]:{gap_locs[i][1]<file[1]}")
            print(f"The result of gap_locs[i][0]>=file[0]{gap_locs[i][0] >= file[0]}")'''
            if (gap_locs[i][1] < file[1]) and (gap_locs[i][0] >= file[0]):
                for j in range(file[0]):
                    expanded[gap_locs[i][1]+j] = file[2]
                    expanded[file[1]+j] = '.'
                change = True
                '''
                print(f"The value being considered is {file[2]}")
                print(f'The gap is now at {gap_locs[i][1]} with length {gap_locs[i][0]}')'''
                break
        if change:
            gap_locs = []
            for i in range(len(expanded)):
                if expanded[i] == '.':
                    if len(gap_locs) == 0:
                        gap = [1,i]
                        gap_locs.append(gap)
                    else:
                        if gap_locs[-1][0]+gap_locs[-1][1] == i:
                            gap_locs[-1] = [gap_locs[-1][0]+1,gap_locs[-1][1]]
                        else:
                            gap_locs.append([1,i])
            #print(gap_locs)
    pt_2_sum = checksum(expanded)
    print(f"The answer to part two is {pt_2_sum}")
    #print(expanded)
    return 0

def main():
    file = open('input.txt','r')
    for line in file:
        string_ver = line[:-1]
    expanded = []
    gap_locs = []
    file_locs = []
    id = 0
    for i in range(len(string_ver)):
        if i % 2 == 0:
            if i == 0:
                file_locs.append([int(string_ver[i]),0,str(id)])
            else:
                file_locs.append([int(string_ver[i]),len(expanded),str(id)])
            for i in range(int(string_ver[i])):
                expanded.append(str(id))
            if string_ver[i] != '0':
                id +=1
        else:
            if string_ver[i-1] == '0':
                print("In addition")
                gap_locs[-1] == [gap_locs[-1][0]+int(string_ver[i]),gap_locs[-1][1]]
            else:
                gap_locs.append([int(string_ver[i]),len(expanded)])
            for i in range(int(string_ver[i])):
                expanded.append('.')
    print()
    pt_1_expanded = copy.copy(expanded)
    pt_1(pt_1_expanded)
    pt_2(expanded,gap_locs,file_locs)

main()