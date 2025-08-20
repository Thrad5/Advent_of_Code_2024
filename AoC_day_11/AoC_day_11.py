"""
Created on Wed Dec  11 17:16:59 (GMT: +00:00 ) 2024

@author: ram86
"""
import math
import time
import matplotlib.pyplot as plt

def pt_1(stones, passes):
    t0 = time.time()
    for i in range(passes):
        new_passes = []
        for j in stones:
            if j == 0:
                new_passes.append(1)
            elif math.floor(math.log10(j)) %2 == 1:
                pow = 10**math.ceil(math.floor(math.log10(j))/2)
                new_passes.append(int(j//(pow)))
                new_passes.append(int(j%pow))
            else:
                new_passes.append(j*2024)
        stones = new_passes
    t1 = time.time()
    print(f"There are {len(stones)} stones")
    print(f"This took {t1-t0} seconds to complete")
    return 0



def pt_2(stones, passes):
    t0 = time.time()
    stone_dict = {}
    for stone in stones:
        if str(stone) in stone_dict:
            stone_dict[str(stone)] += 1
        else:
            stone_dict[str(stone)] = 1
    num_unique = [len(stone_dict)]
    change_in_num = []
    for i in range(passes):
        new_dict = {}
        for key in stone_dict:
            if key == "0":
                if "1" in new_dict:
                    new_dict["1"] += stone_dict[key]
                else:
                    new_dict["1"] = stone_dict[key]
            elif math.floor(math.log10(int(key))) % 2 == 1:
                pow = 10**math.ceil(math.floor(math.log10(int(key)))/2)
                key1 = str(int(int(key)//pow))
                key2 = str(int(int(key)%pow))
                if key1 in new_dict:
                    new_dict[key1] += stone_dict[key]
                else:
                    new_dict[key1] = stone_dict[key]
                if key2 in new_dict:
                    new_dict[key2] += stone_dict[key]
                else:
                    new_dict[key2] = stone_dict[key]
            else:
                to_inc = int(key) *2024
                if str(to_inc) in new_dict:
                    new_dict[str(to_inc)] += stone_dict[key]
                else:
                    new_dict[str(to_inc)] = stone_dict[key]
        stone_dict = new_dict
        change_in_num.append(len(stone_dict) - num_unique[-1])
        num_unique.append(len(stone_dict))
    pt_2_sum =0
    for key in stone_dict:
        pt_2_sum += stone_dict[key]
    t1 = time.time()
    print(f"There are {pt_2_sum} stones")
    print(f"This took {t1-t0} seconds to complete")
    return num_unique, change_in_num

def main():
    inp = [0,1,10,99,999]
    passes = 1000
    print(f"Trying with {passes} passes.")
    unique, change = pt_2(inp,passes)
    #pt_1(inp,passes)
    plt.figure()
    plt.plot(unique)
    plt.show()
    plt.figure()
    plt.plot(change)
    plt.show()
main()