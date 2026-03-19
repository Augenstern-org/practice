list = ["apple", "banana", "cola", "dig", "elements", "freedom", "go", "hello world", "I", "jazz kick"]

def only_leng_string(target, leng):
    rlist = []
    for i in target:
        if len(i) < leng:
            continue
        rlist.append(i)
    print(rlist)

#only_leng_string(list, 4)

def del_forbidden_words(alist, forbidden):
    rlist = []
    for string in alist:
        is_allow = True
        for char in string:
            if char in forbidden:
                is_allow = False
                break
        if is_allow:
            rlist.append(string)
    print(rlist)

#del_forbidden_words(list, "c")

def swap_list_ele(fir, sec):

