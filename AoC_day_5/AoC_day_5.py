class filter():
    def __init__(self,after,before):
        self.target_num = after
        self.to_filter = [before]
    def checkValidity (self, row):
        if (self.target_num in row):
            for i in range(0,len(row)):
                if (row[i] != self.target_num):
                    for j in range(0,len(self.to_filter)):
                        if (row[i] == self.to_filter[j]):
                            return False, i
                else:
                    break
        return True, 0
    def printFilter(self):
        print(f"{self.target_num} must be before {self.to_filter} if they are present")
def orderCorrectly (row, filt):
    test, to_change = filt.checkValidity(row)
    while not test:
        index = row.index(filt.target_num)
        row[index] = row[to_change]
        row[to_change] = filt.target_num
        test, to_change = filt.checkValidity(row)
    return row
def main():
    f = open("./input.txt", 'r')
    in_2nd_hlf = False
    lst_fltr = []
    updates = []
    for line in f:
        if (line == "\n"):
            in_2nd_hlf = True
            continue
        line = line[:-1]
        if(in_2nd_hlf):
            seperated = line.split(',')
            temp = list(map(int,seperated))
            updates.append(temp)
            if(len(temp)%2 == 0):
                print("There are evens")
        else:
            seperated = line.split('|')
            after = int(seperated[0])
            before = int(seperated[1])
            if (lst_fltr == []):
                lst_fltr.append(filter(after,before))
            else:
                not_present = True
                for i in range(0,len(lst_fltr)):
                    test = lst_fltr[i]
                    if (test.target_num == after):
                        not_present = False
                        test.to_filter.append(before)
                        break
                if (not_present):
                    lst_fltr.append(filter(after,before))
    pt_1_sum = 0
    invalid_rows = []
    for line in updates:
        midpoint = len(line)//2
        valid = True
        for filt in lst_fltr:
            test, null = filt.checkValidity(line)
            if (not test):
                valid = False
        if(valid):
            pt_1_sum += line[midpoint]
        else:
            invalid_rows.append(line)
    print(f"The answer to part 1 is: {pt_1_sum}")
    pt_2_sum = 0
    for line in invalid_rows:
        mst_cntu = True
        while mst_cntu:
            for filt in lst_fltr:
                line = orderCorrectly(line,filt)
            for filt in lst_fltr:
                check, null = filt.checkValidity(line)
                if (check):
                    mst_cntu = False
                else:
                    mst_cntu = True
                    break
        valid = True
        midpoint = len(line)//2
        for filt in lst_fltr:
            test, null = filt.checkValidity(line)
            if(not test):
                valid = False
        if(valid):
            pt_2_sum += line[midpoint]
        else:
            print(f"Something's not right didn't finish sorting with row: {line}")
    print(f"The Solution for part 2 is: {pt_2_sum}")
main()