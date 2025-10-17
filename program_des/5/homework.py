def shift(alist):
    temp = alist[-1]
    for index in range(len(alist)-1, 0, -1):
        alist[index] = alist[index - 1]
    alist[0] = temp
    return alist

def is_sorted(alist):
    for index in range(0, len(alist)-1):
        if alist[index] > alist[index + 1]:
            print("False")
            return False
    print("True")
    return True

def has_dups(alist):
    for index in range(0, len(alist)):
        for check_index in range(index + 1, len(alist)):
            if alist[index] == alist[check_index]:
                print("True")
                return True
    print("False")
    return False
