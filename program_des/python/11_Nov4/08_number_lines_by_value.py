'''
Write a function number_lines_by_value(filename) that receives as input:
- filename: the name (string) of a text file. Each line contains zero or more integer values, separated by any number of spaces.

It returns a dictionary (sorted by key, in ascending order) where:
- each key is an integer value that appears at least once in the file,
- each value is a list of all the line numbers (starting from 0) where that integer appears (multiple times on the same line count as one entry for that line).

To help organize your solution, you can implement and use these helper functions:

1. read_numbers_by_line(filename): Reads the file line by line and returns a list of sets, where each set contains all unique integer values present in that line.

2. build_number_index(lines_sets): Takes the output of read_numbers_by_line and returns the unsorted dictionary mapping number to the list of line numbers on which it appears.

3. sort_by_key(d): Takes a dictionary and returns a new dictionary sorted by its keys in ascending order.

4. number_lines_by_value(filename): Uses the above helper functions to implement the required functionality.

Example:
If the file "numbers.txt" contains:
  7  3 3 2
  4 7
  2    4 5
  4 7 7 8
then, after calling:
number_lines_by_value("numbers.txt")
output: {
    2: [0, 2],
    3: [0],
    4: [1, 2, 3],
    5: [2],
    7: [0, 1, 3],
    8: [3]
}
'''

def read_numbers_by_line(filename):
    # Your implementation here
    pass

def build_number_index(lines_sets):
    # Your implementation here
    pass

def sort_by_key(d):
    # Your implementation here
    pass

def number_lines_by_value(filename):
    # Your implementation here
    pass
