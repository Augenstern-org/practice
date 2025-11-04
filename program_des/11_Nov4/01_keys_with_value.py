'''
Write a function keys_with_value(d, value) that receives as input:
- d: a dictionary where each key is an integer and each value is a list of integers.
- value: an integer.

It returns a set containing all the keys from d whose value list contains the given integer.

Example:
d = {
    0: [1, 4, 5],
    1: [3, 5, 7, 9],
    2: [5, 8],
    3: [10, 11]
}
keys_with_value(d, 5)
output: {0, 1, 2}
'''

d = {
    0: [1, 5, 4, 32, 4],
    1: [3, 5, 7, 9],
    2: [5, 8, 3, 12],
    3: [10, 11, 18, 5, 32],
    4: [1, 2, 3, 4],
    5: [6, 7, 8, 9, 5]
}

def keys_with_value(d, value):
    # Your implementation here
    rlist = []
    for i in d:
        if value in d[i]:
            rlist.append(i)
    rlist.sort()
    return rlist
    pass

print(keys_with_value(d, 32))
