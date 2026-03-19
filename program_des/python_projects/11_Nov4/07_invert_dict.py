'''
Write a function invert_dict_lists_sorted(d) that receives as input:
- d: a dictionary where each key is a string, and each value is a list of integers.

It returns a new dictionary where:
- each key is an integer that appeared in any value list of d,
- the corresponding value is a list of all strings from the original dictionary whose value list contained that integer, sorted in ascending order.

Example:
d = {
    "one": [1, 2, 3],
    "two": [2, 4],
    "three": [1, 4, 5],
    "Four": [1, 5]
}
invert_dict_lists_sorted(d)
output: {
    1: ["Four", "one", "three"],
    2: ["one", "two"],
    3: ["one"],
    4: ["three", "two"],
    5: ["Four", "three"]
}
'''

def invert_dict_lists_sorted(d):
    # Your implementation here
    pass
