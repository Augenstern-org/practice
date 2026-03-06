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
Define the function func1(int_list, m, n, outputfilename) that takes as its
input a list of integers int_list, two integers m and n and a
string outputfilename.
The function returns a new list with all the numbers 
of the list that are divisible for m and greater than n.
The list must be sorted in increasing order.
Moreover, the function must write the numbers of the list one by one in
the same line, separated by a space and terminated by a new line character
in a new file named outputfilename.

Example:
    func1([16, 14, 10, 4, 2, 1, 12], 4, 8) should return the list
    [12, 16] and write 12 16 in the outputfile
    
'''
def func1(int_list, m, n, outputfilename):
    ## Write your code here
    pass

# print(func1([16, 14, 10, 4, 2, 1, 12], 4, 8, 'func1/out01.txt'))

# %% ----------------------------------- FUNC2 ------------------------- #
'''func2: 20 marks
Define the function func2(filename) that receives a string representing
the name of a file. The file contains several words separated by spaces,
commas and semicolon. The function must find all the words representing
an integer number and must return the sum of all numbers represented
by the strings found.
'''
def func2(namefile):
    ## Write your code here
    pass

# print(func2('func2/in01.txt'))

# %% ----------------------------------- FUNC3 ------------------------- #
''' func3: 20 marks
Define a function func3(L0, L1) that receives 2 lists L0 and L1.
The first list L0 contains strings S0, S1, ... Sn-1,
the second list L1 contains positive integers I0, I1, ... In-1.
The function returns a string obtaining by concatenating each string
Sj repeated Ij times.
For example, if L0 = ['ab', 'o o'] and L1 = [2, 3] the function returns:
'ababo oo oo o'.
'''

def func3(L0, L1):
    ## Write your code here
    pass

# print(func3(['ab', 'o o'], [2, 3]))

# %% ----------------------------------- FUNC4 ------------------------- #
""" func4: 40 marks
Define a function func4(inputfilename, outputfilename) that receives two
strings representing names of file.   The function must read the file named
inputfilename and write to a new file named outputfilename.
The file inputfilename contains several lines with numbers (float or int)
separated by a comma and optionally by zero or more whitespaces.
For each line of the input file, the function must write in the
correspondent file of the output file the sum of all the numbers in an
even position minus the sum of all the numbers in an odd position
rounded at the second decimal digit.
Positions start from 0 (an even number).
The function must return the maximum value written in the file.
"""

def func4(inputfilename, outputfilename):
    ## Write your code here
    pass
                    
# print(func4('func4/in01.txt', 'func4/out01.txt'))

###########################################################################
if __name__ == '__main__':
    # your tests go here
    print('*'*50)
    print('You have to run grade.py if you want to debug with the automatic grader.')
    print('Otherwise you can insert here you code to test the functions but you have to write your own tests')
    print('*'*50)
