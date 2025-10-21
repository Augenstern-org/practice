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

#file_longest_word(test)





def cleand(text):
    to_replace = []                         # 新建一个列表用来维护需要替换的字符
    for char in text:                       # 开始逐字读取传入变量text的值
        if not char.isalpha():              # 如果当前字符不是字母
            if char not in to_replace:          # 并且这个字符不再列表之中
                to_replace.append(char)         # 那么添加这个字符到列表之中
                                            # （在列表中则不进行任何操作）
    for char in to_replace:                 # 将传入变量text之中的所有的非字母字符替换成空格
        text = text.replace(char, ' ')

# 效果大概是：
# text = "This/is\an~apple.OK!"
# 输出应该为：
# "This is an apple OK "



