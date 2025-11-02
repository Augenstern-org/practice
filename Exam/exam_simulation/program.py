#!/usr/bin/env python3
# -*- coding: utf-8 -*-

################################################################################
################################################################################
################################################################################

""" Operations to carry out FIRST:
 1) Save this file as program.py
 2) Assign the variables below with your
    NAME, SURNAME and STUDENT ID NUMBER

To pass the exam you must:
    - solve at least 3 exercises of type func AND
    - obtain a score greater than or equal to 18

The final grade is the sum of the marks of the solved problems.

IMPORTANT: set DEBUG = True in `grade.py` to improve debugging; but
remember that recursion is tested (and graded) only if DEBUG = False
"""

name = "AME"
surname = "URNAME"
student_id = "ATRICULATION NUMBER"


# %% ----------------------------------- FUNC1 ------------------------- #
'''func1: 2 marks
Define the function func1(D) that receives as a parameter a dictionary
D, in which each key is a positive integer N and the corresponding value
is a list of characters L.
The function returns a list in which each item is a string obtained by repeating
N times each of the characters in L. The list is sorted alphabetically,
in descending order.
For example, if D = {2 : ['s', 'u', 'e'], 3 : ['q', 'a'],
the function will return:
L = ['uu', 'ss', 'qqq', 'ee', 'aaa']
'''
def func1(D):
    rlist = []
    for i in D:
        for j in D[i]:
            rlist.append( "".join(j)*i )
    rlist = sorted(rlist, reverse=True)
    return rlist
    ## Write your code here
    pass

# %% ----------------------------------- FUNC2 ------------------------- #
''' func2: 2 marks
Define the function func2(L) that gets as parameter a list L of N lists.
Each list in L can be empty or contain a single list, defined the same way.
The function returns a list of N integers, in which the i-th value
is the number of lists nested in the list at the i-th position in L.
For example, if L = [ [[]], [], [[[]], [[]], [[[[]]]], [], [[[]] ]
the function will return: [1, 0, 2, 1, 3, 0, 2]
'''
def func2(L):
    rlist = []
    for i in L:
        temp = str(i)
        c = temp.count("[") - 1
        rlist.append(c)
    return rlist
    ## Write your code here
    pass

# %% ----------------------------------- FUNC3 ------------------------- #
''' func3: 2 marks
Define the function func3(S) that receives as input a string containing
words separated by commas and, optionally, also by spaces.
The function should extract the words from S, considering only those that
begin with a vowel, and insert them into another list, sorted
alphabetically without considering the difference between uppercase and lowercase.
For example, if S = “Brad,ALIce, keVin, oscar, Dana, UMA,ian, Zoe”
the function will return: ['ALIce', 'ian', 'oscar', 'UMA']
'''

def func3(S):
    S = S.replace(",", " ")
    temp = S.split()
    rlist = []
    v = ["a", "e", "i", "o", "u"]
    for i in temp:
        if i[0].lower() in v:
            rlist.append(i)
    rlist = sorted(rlist, key= lambda x: x.lower())
    return rlist
    ## Write your code here
    pass

#%% ----------------------------------- FUNC4 ------------------------- #
""" func4: 6 marks
Define the function `func4(input_filepath, output_filepath)` that reads a file
located at `input_filepath` and writes the identified words to a new file at
`output_filepath`. Words in the input file are separated by various delimiters,
including newlines, spaces, tabs, commas, or semicolons. 

The task is to group these words by their last letter without distinguishing
between uppercase and lowercase letters. Words are considered identical if
they are the same when case is ignored, meaning each word should only be
counted once. 

For each group of words, the output file should include a line formatted as
follows:

`<lowercase letter>: <word count>`

In this format, the initial letter is in lowercase, followed by a colon and a
space. After the colon and space, the number of words ending with that letter
is provided, regardless of the case of the letters in the words. The lines in
the output file should be ordered in descending alphabetical order based on
the letter before the colon.

Please note that there should be no space at the end of each line in the
output file, but each line should end with a carriage return.

The function should return the total number of words in the input file,
including duplicates.
For example:

contents of func4/func4_in1.txt:
GE
wOa;II,see ua;PAO,oA;wOA
pao iu;jJa,kE

By calling the function as:
n = func4(“func4/func4_in1.txt”, “func4/func4_out1.txt”)

the expected contents of func4/func4_out1.txt is:
u: 1
o: 1
i: 1
e: 3
a: 4

and the value of n will be 12
"""

def func4(input_filepath, output_filepath):
    rlist = []
    with open(input_filepath, 'r') as inf:
        with open(output_filepath, 'w') as ouf:
            lines = inf.readlines()
            for line in lines:
                line = line.replace(",", " ")
                line = line.replace(";", " ")
                line = line.replace("\t", " ")
                temp = line.split()
                for i in temp:
                    rlist.append(i)
            # 去重
            s = set()
            for i in rlist:
                if i.lower() not in s:
                    s.add(i.lower())
            # 统计
            d = dict()
            for i in s:
                if i[-1] not in d:
                    d[str(i[-1])] = 1
                else:
                    d[str(i[-1])] += 1
            # 写入
            w = []
            for i in d:
                w.append(str(i + ": " + str(d[i])))
            w = sorted(w, reverse= True)
            for i in w:
                ouf.write(i + "\n")
    return len(rlist)
    ## Write your code here
    pass


###################################################################################
if __name__ == '__main__':
    # your tests go here
    print('*'*50)
    print('You have to run grade.py if you want to debug with the automatic grader.')
    print('Otherwise you can insert here you code to test the functions but you have to write your own tests')
    print('*'*50)
