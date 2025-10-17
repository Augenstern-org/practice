list = ["1d2r45", "321j2", "fjwj1", "jwjci1", "9n3nck", "evil21"]

def select_and_sum_up(target):
    rval = 0
    for i in range(0,len(target)):
        for j in target[i]:
            try:
                temp = int(j)
                rval += temp
            except ValueError:
                continue
    print(rval)
    return rval


def selcet_max_num(target):
    rval = []
    max_num = 0
    for i in range(0,len(target)):
        sum_temp = 0
        for j in target[i]:
            try:
                temp = int(j)
                #print("temp:",temp)
                sum_temp += temp
            except ValueError:
                continue
        #print("sum_temp:", sum_temp)
        rval.append(sum_temp)
    for i in range(0, len(rval)):
        #print("max_num:", max_num, " rval[", i, "]: ", rval[i], sep = "")
        if rval[i] > max_num:
            max_num = rval[i]
    print(max_num)
    return max_num

def dont_use(word, forbidden):
    for j in word:
        if j in(forbidden):
            print("False")
            return False
    print("True")
    return True

def use_only(word, allow):
    for i in word:
        if i in(allow):
            continue
        print("False")
        return False
    print("True")
    return True


def use_exactly(word, required):
    is_all_used = []
    for i in range(len(required)):
        is_all_used.append(0)
    for j in word:
        if j in required:
            is_all_used[required.find(j)] = 1
    for k in is_all_used:
        if k == 0:
            print("false")
            return False
    print("true")
    return True

use_exactly("applebanana","aplebn")

