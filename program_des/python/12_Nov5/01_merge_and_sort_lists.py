'''
Write a function merge_and_sort_lists_by_key(paired_list) that receives as input:
- paired_list: a list of tuples, where each tuple contains:
    - a string key
    - a list of integers

The function returns a dictionary where:
- each key is one of the string keys from paired_list,
- the corresponding value is the merged list of all integers from lists associated with that key (from all tuples in paired_list), 
  with duplicates removed and sorted in ascending order.

Example:
'''
paired_list = [
    ("cat", [7, 3]),
    ("dog", [1, 4]),
    ("cat", [2, 7])
]
'''
merge_and_sort_lists_by_key(paired_list)
output: {'cat': [2, 3, 7], 'dog': [1, 4]}
'''

def rm_the_same(lst):
    rlist = []
    lst.sort()
    for item in lst:
        if item not in rlist:
            rlist.append(item)
    return rlist


def merge_and_sort_lists_by_key(paired_list):
    # Your implementation here
    d = dict()
    for item in paired_list:
        if item[0] not in d:
            d[item[0]] = item[1]
        d[item[0]] += item[1]
    for ani in d:
        d[ani] = rm_the_same(d[ani])
    print(d)
    pass

merge_and_sort_lists_by_key(paired_list)
