#d = {1:["I"], 2:["o"], 3:["A"], 4:["e"], 5:["u"]}
#print(d)
#
#rlist = []
#for i in d:
#    rlist.append("".join(d[i]))
#
#print(rlist)
#
#rlist = sorted(rlist, key= lambda x: x.lower())
#
#print(d)
#print(rlist)
#
#

def func2(L):
    r = []
    for i in L:
        i = str(i)
        r.append(i.count('[')-1)
    print(r)
    return r

L = [ [[]], [], [[[]]], [[]], [[[[]]]], [], [[[]]]]
#func2(L)

counter = 1
def f3(lst, c):
    global c = 1
    if is
