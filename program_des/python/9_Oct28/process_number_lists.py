'''
Write a function process_number_lists(list1, list2) to:
- Receive as input two lists of integers.
- Remove from the first list all numbers that also appear in the second list.
- Keep only unique numbers from the first list (remove duplicates).
- Filter the remaining numbers to keep only those greater than 10.
- Return the final result as a sorted list (ascending order).

Subfunctions:
- remove_common_numbers(list1, list2): Receives two lists, returns a new list with elements from list1 not in list2.
- unique_numbers(numbers): Receives a list, returns a list of unique numbers.
- filter_greater_than(numbers, threshold): Receives a list, returns only those numbers greater than threshold.
- sort_numbers(numbers): Receives a list, returns the sorted list.

Example usage:
    >>> a = [5, 20, 20, 30, 4, 11, 50, 7]
    >>> b = [20, 11, 100]
    >>> process_number_lists(a, b)
    [30, 50]

'''

def remove_common_numbers(list1, list2):
    rlist = []
    s1 = set(list1)
    s2 = set(list2)
    s3 = s1 - (s1 & s2)
    for i in s3:
        rlist.append(i)
    rlist.sort()
    return rlist
    pass  # Your code here

def unique_numbers(numbers):
    rlist = []
    for i in numbers:
        if i not in rlist:
            rlist.append(i)
    pass  # Your code here

def filter_greater_than(numbers, threshold):
    rlist = []
    for i in numbers:
        if i > 10:
            rlist.append(i)
    return rlist
    pass  # Your code here

def sort_numbers(numbers):
    pass  # Your code here

def process_number_lists(list1, list2):
    pass  # Your code here
