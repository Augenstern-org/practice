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

name = "NAME"
surname = "SURNAME"
student_id = "MATRICULATION NUMBER"


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
    ## Write your code here
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
    ## Write your code here
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
    ## Write your code here
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
    ## Write your code here
    pass

###################################################################################
if __name__ == '__main__':
    # your tests go here
    print('*'*50)
    print('You have to run grade.py if you want to debug with the automatic grader.')
    print('Otherwise you can insert here you code to test the functions but you have to write your own tests')
    print('*'*50)
