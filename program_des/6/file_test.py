import string
import re

def strip_punctuation(text):
    return re.sub(r'[^\w\s]', '', text)

def file_char_counter(filename):
    n = 0
    f = open(filename, 'r')
    list = []
    line = f.readline()
    while line:
        line = strip_punctuation(line)
        for char in line:
            n += 1
        line = f.readline()
    print(n)
    return n

def file_longest_word(filename):
    word = ""
    list = []
    temp = ""
    with open(filename, 'r') as f:
        while True:
            c = f.read(1)
            if not c:
                if len(word) < len(temp):
                    word = temp
                temp = ""

    print(word, "in file:", filename)
    return word

test = "test.txt"

#file_char_counter(test)

file_longest_word(test)
