def sum_up(a, b):
    sum = b
    while a < b:
        sum = sum + a
        a = a + 1
    print(sum)
    return sum

def multi_table():
    a = b = 1
    while b != 11:
        while a != b+1:
            rVal = a * b
            print(a, "*", b, "=", rVal, sep = "", end = " ")
            a += 1
        print("")
        b += 1
        a = 1

def power_table(row, line):
    for i in range(1, row+1):
        for j in range(1, line+1):
            rval = i ** j
            print(i, "**", j, "=", rval, sep = "", end = " ")
        print("")

def BIN_to_DEC(target):
    rval = 0
    tIndex = len(str(target))
    for digit in range(0, tIndex):
        rval += 2 ** (tIndex - digit)
    print(rval)


def averange(num_list):
    sum = 0
    for i in range(0, len(num_list)):
        sum += num_list[i]
    ave = sum / len(num_list)
    print(ave)

l = [1,2,3,4,5,6,7,8,9,10,11]
averange(l)
