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

select_and_sum_up(list)
