'''
Write a function count_max_elements_per_key(data_dict) that receives as input:
- data_dict: a dictionary where each key is a string and each value is a list of tuples of the form (int, float).

The function must return a dictionary where:
- Each key is the same as in data_dict.
- The corresponding value is the number of tuples in the list for that key whose integer part is equal to the maximum integer for that list.

To organize your solution, you are encouraged to implement and use helper functions, such as:
- max_int_in_list(tuple_list): Returns the maximum integer value found in tuple_list.
- count_tuples_with_max_int(tuple_list): Returns how many tuples in tuple_list have the integer part equal to the maximum.

Example:
data_dict = {
    'a': [(2, 1.7), (5, 2.0), (5, 8.3)],
    'b': [(1, 0.4), (3, 7.1), (3, 4.8), (2, 2.2)],
    'c': []
}

count_max_elements_per_key(data_dict)
output: {'a': 2, 'b': 2, 'c': 0}
# For 'a', max int is 5, two tuples [(5, 2.0), (5, 8.3)] have integer 5.
# For 'b', max int is 3, two tuples [(3, 7.1), (3, 4.8)] have integer 3.
# For 'c', the list is empty, so count is 0.
'''

def count_max_elements_per_key(data_dict):
    # Your implementation here
    pass
