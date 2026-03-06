'''
Write functions to work with sets and practice union, difference, and subset operations.

Your program should:
- Given two lists of integers, convert each to a set.
- Find and return the union of the two sets.
- Find and return the difference between the first and the second set.
- Add a list of integers to the first set (modifying it in place).
- Remove all elements in the second set from the first set (modifying it in place).
- Check if the second set is a subset of the first set.

Functions:
- list_to_set(int_list): Takes a list of integers and returns a set.
- set_union(s1, s2): Returns the union of sets s1 and s2.
- set_difference(s1, s2): Returns the difference of sets s1 and s2 (elements in s1 not in s2).
- add_list_to_set(s, int_list): Adds all elements from int_list into set s (modifies s in place).
- remove_set_items(s1, s2): Removes all elements in s2 from s1 (modifies s1 in place).
- is_subset(s1, s2): Returns True if s2 is a subset of s1, False otherwise.

Example usage:
    >>> s1 = list_to_set([10, 20, 30, 40])
    >>> s2 = list_to_set([30, 40, 50, 60])
    >>> set_union(s1, s2)
    {10, 20, 30, 40, 50, 60}
    >>> set_difference(s1, s2)
    {10, 20}
    >>> add_list_to_set(s1, [70, 80])
    >>> s1
    {10, 20, 30, 40, 70, 80}
    >>> remove_set_items(s1, s2)
    >>> s1
    {10, 20, 70, 80}
    >>> is_subset(s1, s2)
    False
'''

def list_to_set(int_list):
    return r = set(int_list)
    pass  # Your code here

def set_union(s1, s2):
    return r = s1.union(s2)
    pass  # Your code here

def set_difference(s1, s2):
    pass  # Your code here

def add_list_to_set(s, int_list):
    pass  # Your code here

def remove_set_items(s1, s2):
    pass  # Your code here

def is_subset(s1, s2):
    pass  # Your code here
