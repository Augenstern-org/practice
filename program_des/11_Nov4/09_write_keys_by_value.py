'''
Write a function write_keys_by_value(d, filename) that receives as input:
- d: a dictionary where each key is a string and each value is a list of positive integers.
- filename: the name (string) of a file to write.

The function writes a file so that, for each non-negative integer N from 0 up to the largest value present in any value list in d,
- line N of the file contains all the keys from d whose value list contains N, separated by spaces.
- The keys written on each line must be sorted in descending order, ignoring case (e.g., 'Zeus' comes before 'apple').
- If no key corresponds to a given N, that line will be empty (i.e., a blank line).
- Lines appear in ascending order by N (so the line number is always N).

To help organize your solution, you are encouraged to structure your work using the following helper functions:

1. invert_dict(d): Returns a dictionary whose keys are all the integers appearing in any value list of d, and whose values are the list of keys from d that contain that integer in their value list.

2. sort_keys_desc_case_insensitive(keys): Receives a list of strings and returns a new list of those strings sorted in descending order, ignoring case.

3. write_keys_by_value(d, filename): Uses invert_dict and sort_keys_desc_case_insensitive to write the required file, with one line for every integer from 0 to the max present. Each line contains the sorted keys (descending, case-insensitive) or empty for values not present in any key.

Example:
Suppose this code is run:
d = {
    "apple": [0, 2],
    "Banana": [2, 3],
    "zeus": [0, 3, 5],
    "Mango": [5]
}
write_keys_by_value(d, "output.txt")

The contents of output.txt will be:
zeus apple

Banana apple
zeus Banana

zeus Mango

(because:
- line 0: keys are zeus, apple (descending, ignoring case: "zeus" > "apple")
- line 1: no key has 1, so line is blank
- line 2: keys are Banana, apple
- line 3: keys are zeus, Banana
- line 4: no key has 4, so line is blank
- line 5: keys are zeus, Mango
)
'''

def invert_dict(d):
    # Your implementation here
    pass

def sort_keys_desc_case_insensitive(keys):
    # Your implementation here
    pass

def write_keys_by_value(d, filename):
    # Your implementation here
    pass
