'''
Write a function write_sorted_words_from_file(input_path, output_path) that receives as input:
- input_path: the path to a text file to read (filein)
- output_path: the path to a text file to write (fileout)

The function must:
- read all words from the input file,
- write all words to the output file in a single line separated by a comma and a space,
- sort the words by:
    1. length, in decreasing order,
    2. number of vowels (a, e, i, o, u), in increasing order in case of tie,
    3. alphabetical order in case of remaining ties.

The function returns the number of words found in the input file.

Example:
If filein contains:
apple zoo banana orange kiwi

write_sorted_words_from_file("filein.txt", "fileout.txt")
# the output file will contain:
banana, orange, apple, kiwi, zoo

and the function returns: 5
'''

def vowels_in_word(word):
    pass

lambda x: [len(x), vowels_in_word(x), x.lower()]

def write_sorted_words_from_file(input_path, output_path):
    # Your implementation here
    pass

