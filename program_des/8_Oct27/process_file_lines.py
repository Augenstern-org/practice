'''
Write functions to process the contents of a text file using lists and string functions, and enclose everything into a main function that receives as parameters the input file name, the output file name, and the word to use for filtering lines.

Your program should:
- Open the input text file and read all its lines into a list.
- For each line, remove leading and trailing whitespace (but keep spaces between words).
- Convert all lines to lowercase.
- Filter the lines to keep only those containing the given word or substring (case-insensitive).
- Write the filtered lines to the output file, one line per entry.

Functions:
- read_lines_from_file(filename): Opens the file in read mode and returns a list of all lines.
- clean_lines(lines): Strips leading/trailing whitespace and newline characters from each line.
- to_lowercase(lines): Returns a new list with all lines in lowercase.
- filter_lines(lines, substring): Returns only the lines that contain the given substring.
- write_lines_to_file(filename, lines): Opens the file in write mode and writes each line from the list onto a new line in the file.
- process_file_lines(in_filename, out_filename, keyword): Main function tying everything together as described above.

Example:
If the text file `text.txt` contains:
Hello World  
PYTHON is fun  
HELLO again  
Bye  

Then:
    >>> process_file_lines('text.txt', 'filtered.txt', 'hello')

The new file `filtered.txt` will contain:
hello world  
hello again
'''

def read_lines_from_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    return lines
    pass  # Your code here

def clean_lines(lines):
    rlist = []
    for line in lines:
        line = line.strip()
        rlist.append(line)
    return rlist
    pass  # Your code here

def to_lowercase(lines):
    rlist = []
    for line in lines:
        line = line.lower()
        rlist.append(line)
    return rlist
    pass  # Your code here

def filter_lines(lines, substring):
    rlist = []
    for line in lines:
        if substring in line:
            rlist.append(line)
    return rlist
    pass  # Your code here

def write_lines_to_file(filename, lines):
    with open(filename, 'w') as f:
        for line in lines:
            f.write(line + "\n")
    pass  # Your code here

def process_file_lines(in_filename, out_filename, keyword):
    write_lines_to_file(out_filename,filter_lines(to_lowercase(clean_lines(read_lines_from_file(in_filename))),keyword))
    pass  # Your code here

process_file_lines("test.txt", "out.txt", "hello")
