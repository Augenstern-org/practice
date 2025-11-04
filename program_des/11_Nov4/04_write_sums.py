'''
Write a function sum_unique_numbers_per_line(input_filename, output_filename) that receives as input:
- input_filename: the name of a text file where each line contains a sequence of integers separated by commas.
- output_filename: the name of an output text file.

The function must process each line by extracting all integers, keeping only the unique values, and computing their sum for each line.
Then, write all the sums to the output file, one per line, sorted in ascending order.
The function does not return anything.

To organize your solution, you can implement and use these helper functions:

1. parse_line_to_integers(line): Given a string (a line in the input file), returns a list of the integers it contains.

2. unique_sum(numbers): Given a list of integers, returns the sum of their unique values.

3. sum_unique_numbers_per_line(input_filename, output_filename): Uses the above helpers to process the file as described.

Example:
If "numbers.txt" contains:
  2,5,5,1,8
  4,4,9,2
  7,7,7
  5,2,1

After calling:
sum_unique_numbers_per_line("numbers.txt", "output.txt")
the file "output.txt" will contain:
  7
  8
  15
  16
'''
from functools import reduce

def parse_line_to_integers(line):
    # Your implementation here
    pass

def unique_sum(numbers):
    # Your implementation here
    pass

def sum_unique_numbers_per_line(input_filename, output_filename):
    with open(input_filename, 'r') as inf:
        with open(output_filename, 'w') as ouf:
            rlist = []
            lines = inf.readlines()
            for line in lines:
                line = line.replace(",", " ")
                temp = line.split()
                rlist.append(reduce(lambda x, y: int(x)+int(y), temp))
            rlist.sort()
            for item in rlist:
                ouf.write(str(item) + "\n")
    pass

sum_unique_numbers_per_line("1.txt", "output.txt")