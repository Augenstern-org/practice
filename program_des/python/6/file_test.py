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


def cleand(text):
    to_replace = []
    for char in text:
        if not char.isalpha():
            if char not in to_replace:
                to_replace.append(char)
                #print("add", char,"into list")
    #print(to_replace)
    for char in to_replace:
        text = text.replace(char, ' ')

# 效果大概是：
# text = "This/is\an~apple.OK!"
# 输出应该为：
# "This is an apple OK "


def file_longest_word(filename):
    word = ""
    with open(filename, 'r') as file:
        for line in file:
            cleand(line)
            temp = ""
            for t in line:
                if t == " ":
                    if len(temp) >= len(word):
                        word = temp
                    temp = ""
                    continue
                temp += t
    print('"', word, '"', " in file: ", '"', filename, '"', sep = "")

test = "test2.txt"

#file_char_counter(test)

file_longest_word(test)


