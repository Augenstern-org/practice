'''
Write a function write_words_by_index(word_lists, index_lists, output_path) that receives as input:
- word_lists: a list of lists of strings
- index_lists: a list of lists of integers, with each inner list indicating the order in which words should be selected from the corresponding word list
- output_path: a string, the path to a text file that the function must write

For each list of words in word_lists, the function writes a line to the output file.
The order of words in each output line is determined by the corresponding list in index_lists,
where the integers indicate the indices of the words to write from the word list, in that order.

The function returns the total number of words written to the output file.

Example:
word_lists = [
    ["monkey", "cat"],
    ["panda", "alligator"],
    ["zoo", "zuu", "zotero"]
]
index_lists = [
    [1, 0],         # first word at index 1, then at 0
    [0, 1],         # first word at index 0, then at 1
    [2, 1, 0]       # first word at index 2, then 1, then 0
]

After calling:
write_words_by_index(word_lists, index_lists, "out.txt")
the file "out.txt" will contain:
cat monkey
panda alligator
zotero zuu zoo

and the function returns: 7
'''

def write_words_by_index(word_lists, index_lists, output_path):
    # Your implementation here
    pass
