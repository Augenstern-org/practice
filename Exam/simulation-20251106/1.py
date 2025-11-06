def rm_the_same(lst):
    lst.sort()
    rlist = []
    for i in lst:
        if i not in rlist:
            rlist.append(i)
    return rlist


def func1(L):
    # your code goes here
    common = set()
    all_ch = dict()
    for lst in L:
        lst = rm_the_same(lst)
        for item in lst:
            if item not in all_ch:
                all_ch[item] = 1
            else:
                all_ch[item] += 1
    for i in all_ch:
        if all_ch[i] == len(L):
            common.add(i)
    return common
    pass

L = [[4, 2, 6], [6, 3, 6], [2, 1, 6]]
#print(func1(L))

words = ['apple', 'pear', 'banana', 'tea', 'dog', 'ant']

def unique_ch(word):
    s = set()
    for ch in word:
        if ch not in s:
            s.add(ch)
    return len(s)

def func2(words):
    # your code goes here
    tuple_lst = []
    rd = dict()
    for word in words:
        tuple_lst.append((unique_ch(word), word))
    for t in tuple_lst:
        if t[0] not in rd:
            rd[t[0]] = list()
            rd[t[0]].append(str(t[1]))
        else:
            rd[t[0]].append(str(t[1]))
    for i in rd:
        rd[i].sort()
    return rd
    pass

#print(unique_ch("good"))

#print(func2(words))



#def rm(dict):
    

def func3(int_list, Action):
    # your code goes here
    counter = 0
    list_copy = []
    for i in int_list:
        list_copy.append(i)
    excep = set()
    for j in Action:
        if Action[j] == 'r':
            while j in int_list:
                counter += 1
                int_list.remove(j)
            excep.add(j)            
        if Action[j] == 'a' and j not in excep:
            int_list.append(j)
            excep.add(j)
    for i in list_copy:
        if i not in excep:
            int_list.append(i)
    int_list.sort(reverse=True)
    return counter
    pass


int_list = [7, 3, 6, 5, 7]
Action = {2: 'a', 7: 'r', 4: 'a'}

#int_list = [1, 1, 1, 2, 2, 2, 2]
#Action = {1: 'r', 2: 'r'}


print(func3(int_list, Action))

def func4(pairs):
    # your code goes here
    rlist = sorted(pairs, key = lambda x: [-len(x[1]), x[1], -x[0]])
    return rlist
    pass

pairs = {
    (2, "cat"),
    (2, "fish"),
    (1, "cat"),
    (2, "bat")
}

#print(func4(pairs))

def lower_custom(word):
    rlist = []
    for ch in word:
        if ch.isalpha():
            rlist.append(ch.lower())
        else:
            rlist.append(ch)
    return "".join(rlist)

#print(lower_custom("WorDs0"))

def func5(inputfilename, outputfilename):
    # your code goes here
    # read file
    with open(inputfilename, 'r') as inf:
        lines = inf.readlines()
    # process each line
    count = dict()
    for index in range(len(lines)):
        lines[index] = lines[index].replace(",", " ")
        lines[index] = lines[index].replace(".", " ")
        line_pd = lines[index].split()
        # process each word
        # index -> num of line
        for word in line_pd:
            word_ = lower_custom(word)
            if word_ not in count:
                count[word_] = list()
                count[word_].append(index)
            else:
                count[word_].append(index)
    # sort and process for ouf
    ouf_list = []
    for w in count:
        count[w].sort()
        ouf_list.append((w, count[w]))
    ouf_list = sorted(ouf_list, key= lambda x: x[0], reverse= True)
    print(ouf_list)
    # write
    with open(outputfilename, 'w') as ouf:
        for i in ouf_list:
            ouf.write(str(i[0]) + " ")
            for j in i[1]:
                ouf.write(str(j) + " ")
            ouf.write("\n")
    return count
    pass







i = "simulation-20251106\\func5\\input_example_1.txt"
o = "out1.txt"
#print(func5(i, o))








