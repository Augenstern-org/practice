def func1(int_list, m, n, outputfilename):
    rlist = []
    for i in int_list:
        print("i: ",i)
        if i % m == 0:
            if i > n:
                rlist.append(i)
                print("i/m: ",i/m)
    print(rlist)
    rlist.sort()
    print(rlist)
    with open(outputfilename, 'w') as f:
        for j in range(len(rlist)):
            f.write(str(rlist[j]) + " ")
    return rlist

int_list = [16,14,10,4,2,1,12]

#func1(int_list, 4, 8, "f1.txt")

def func2(namefile):
    with open(namefile, 'r') as f:
        sum = 0
        for line in f:
            line = line.replace(",", " ")
            line = line.replace(";", " ")
            line = line.strip()
            line = line.split()
            if line == []:
                continue
            for i in line:
                try:
                    temp = int(i)
                    sum += temp
                except ValueError:
                    continue
        return sum

f2 = "C:\\Users\\user\\Desktop\\exam251023\\func2\\in01.txt"

#func2(f2)


def func3(L0, L1):
    result = ""
    for i in range(len(L0)):
        result += L0[i] * L1[i]
    return result
    pass


def func4(inputfilename, outputfilename):
    maximum = -100
    with open(inputfilename, 'r') as inf:
        with open(outputfilename, 'w') as ouf:
            for line in inf:
                e_sum = 0
                o_sum = 0
                line = line.replace(",", " ")
                line = line.replace(";", " ")
                line = line.strip()
                line = line.split()
                for i in range(len(line)):
                    if i % 2 == 0:
                        e_sum += float(line[i])
                    else:
                        o_sum += float(line[i])
                r = e_sum - o_sum
                if r > maximum:
                    maximum = r
                ouf.write(str(r) + "\n")
    return maximum
    #pass


i = "C:\\Users\\user\\Desktop\\exam251023\\func4\\in02.txt"
o = "f4.txt"

func4(i, o)

ro





