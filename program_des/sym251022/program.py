#!/usr/bin/env python3
# -*- coding: utf-8 -*-

################################################################################
################################################################################
################################################################################

""" Operations to carry out FIRST:
 1) Save this file as program.py
 2) Assign the variables below with your
    NAME, SURNAME and STUDENT ID NUMBER
 3) When your functions are ready, save the file in the window for the
    collection.

IMPORTANT: set DEBUG = True in `grade.py` to improve debugging; but
remember that recursion is tested (and graded) only if DEBUG = False
"""

name = "Dingbang"
surname = "Li"
student_id = "202521090092"


# %% ----------------------------------- FUNC1 ------------------------- #
'''func1: 20 marks
Define the function func1(int_list, outputfilename) that takes as its
input a list of integers int_list and the name of a file.
The function returns a new list where the element in position i
corresponds to the value obtained summing all the elements of the list
from position i to the last position.
Moreover, the function must write the numbers of the list one by one in
the same line, separated by a space and terminated by a new line character
in a new file named outputfilename.

Example:
    if int_list = [1, 2, 3, 4, 5]
    the new list will be  [15, 14, 12, 9, 5]

'''
def func1(int_list, outputfilename):
    rlist = []
    for index in range(0, len(int_list)):
        sum = 0
        for j in range(index, len(int_list)):
            sum += int_list[j]
        rlist.append(sum)
    with open(outputfilename, 'w') as f:
        for num in rlist:
            f.write(str(num))
            f.write(" ")
    return rlist
    pass

# %% ----------------------------------- FUNC2 ------------------------- #
''' func2: 20 marks
Define a function func2(str1, str2) that takes as input two strings of
the same length and constructs a new string str3 obtained by
considering, for each pair of characters in str1 and str2 in position i,
the smallest one in alphabetical order. The input strings str1 and str2
are made of lower case alphabetical characters. The function returns the
constructed string, all uppercase.

Example:
    func2('plane', 'react') must return the string 'PEACE'

'''
def func2(str1, str2):
    rlist = []
    for i in range(0, len(str1)):
        if str1[i] < str2[i]:
            rlist.append(str1[i])
        else:
            rlist.append(str2[i])
    result = "".join(rlist)
    result = result.upper()
    return result
    pass

# %% ----------------------------------- FUNC3 ------------------------- #
""" func4: 40 marks
Write a function func4(inputfilename, outputfilename) that takes the name
of two string as filenames. 
The function must read the content of the file named inputfilename which
contains several lines of words separated by commas, semicolon or spaces.
For each line of the input file the function must find the word with
the highest unicode character and write it in the corresponding line
of a new file, named outputfilename.
Moreover, the function must returns the word with the highest unicode character
found.

"""
def func3(inputfilename, outputfilename):
    def getMaxUnicode(string):
        max_code = 0
        for i in string:
            if ord(i) > max_code:
                max_code = ord(i)
        return max_code
    def find(list):
        temp = 0
        for i in range(len(list)):
            if int(i) > temp:
                temp = int(i)
        if temp == 0:
            return -1
        else:
            return temp
    global_word = ''
    global_code = 0
    with open(inputfilename, 'r') as inf:
        with open(outputfilename, 'w') as ouf:
            line = inf.readline()
            while line:
                temp = []
                words = line.replace(',', ' ')
                words = line.replace(';', ' ')
                words = line.split()
                for i in words:
                    temp.append(int(getMaxUnicode(i)))
                pos = find(temp)
                if ord(line[pos]) > global_code:
                    global_code = ord(line[pos])
                    global_word = line[pos]
                ouf.write(ord(line[pos]))
                line = inf.readline()
    return global_word
    pass

# %% ----------------------------------- FUNC4 ------------------------- #
""" func4: 40 marks
Write a function func4(list_A, list_B) that takes two lists with the
same number of strings as input.
The function returns a third list of strings.
Each string in position i in the result list
contains the characters in common between the two strings
in position i in list_A and list_B, all in lower case,
in alphabetical order, and ignoring the case they had
in the strings in list_A and list_B.
The characters in common between the two strings in the two
lists can be in whatever position inside the strings.
The strings in list_A and list_B cannot contain repeating
characters, whatever their case.

For example, if list_A = ["aBd", "baC", "cAb"] and
list_B = ["bcE", "dca", "eDf"], the function returns:
["b", "ac", ""]
"""

def func4(list_A, list_B):
    rlist = []
    for i in range(0, len(list_A)):
        a = list_A[i].lower()
        b = list_B[i].lower()
        same_char = []
        for ch in a:
            if ch in b and ch not in same_char:
                same_char.append(ch)
        same_char.sort()
        rlist.append("".join(same_char))
    return rlist
    pass

###################################################################################
if __name__ == '__main__':
    # your tests go here
    print('*'*50)
    print('You have to run grade.py if you want to debug with the automatic grader.')
    print('Otherwise you can insert here you code to test the functions but you have to write your own tests')
    print('*'*50)
