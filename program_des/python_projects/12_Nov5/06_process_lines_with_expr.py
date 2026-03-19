'''
Write a function process_lines_with_expr(input_filename, output_filename, expr) that receives as input:
- input_filename: a string (the name of a text file to read)
- output_filename: a string (the name of a text file to write)
- expr: a string

The file given by input_filename contains a series of words separated by spaces on multiple lines.
The function must locate all lines in input_filename that contain a word equal to expr (ignoring case) and write those lines in the same order to output_filename.

Finally, the function must return a dictionary in which:
- The keys are the numbers (starting from 0) of the lines in the input file that contained a word equal to expr (ignoring case).
- The corresponding value for each key is a triple containing:
    - the total number of characters (including spaces, excluding newlines) on that line,
    - the number of words on that line,
    - the total number of space characters on that line.

To organize your solution, you are encouraged to implement helper functions, such as:
- line_has_word(line, target): Returns True if the line contains a word exactly equal to target (ignoring case).
- line_stats(line): Returns a triple as specified (character count, word count, spaces count).

Note: the first line in the input file should be considered as line 0.

Example:
If 'func4_test1.txt' contains these three lines:
cat bat    rat
Condor baT
Cat cAr CAR

then calling:
process_lines_with_expr('testfile.txt', 'output.txt', 'CAt')
will write the following two lines to 'output.txt':
cat bat    rat
Cat cAr CAR

and return:
{0: (14, 3, 5), 2: (11, 3, 2)}
'''

def process_lines_with_expr(input_filename, output_filename, expr):
    # Your implementation here
    pass
