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

name = "Maurizio"
surname = "Mancini"
student_id = "12345678"

# %% ----------------------------------- FUNC1 ------------------------- #
'''func1: 20 marks

Write a function func1(L) that receives as input:
- L: a list of lists of integers.

The function returns a set containing the numbers that appear
in all of the lists in L.

Example:
L = [[4, 2, 6], [6, 3, 6], [2, 1, 6]]
func1(L)
output: {6}
'''

def rm_the_same(lst):
    lst.sort()
    rlist = []
    for i in lst:
        if i not in rlist:
            rlist.append(i)
    return rlist


def func1(L):
    # your code goes here
    common = set()
    all_ch = dict()
    for lst in L:
        lst = rm_the_same(lst)
        for item in lst:
            if item not in all_ch:
                all_ch[item] = 1
            else:
                all_ch[item] += 1
    for i in all_ch:
        if all_ch[i] == len(L):
            common.add(i)
    return common
    pass

# L = [[4, 2, 6], [6, 3, 6], [2, 1, 6]]
# print(func1(L))
# L = [[1, 2, 3, 4, 5], [2, 3, 4, 5], [3, 4, 5], [4, 5], [5]]
# print(func1(L))
# L = [[20, 15, 10, 5, 0], [100, 105, 5, 200, 205, 5, 15], [5, 5, 5, 5, 15, 15, 15, -1]]
# print(func1(L))
# L = [[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -5], [5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5], [-5, -4, -3, -3, -2, -2, -2, -1, 0, 0]]
# print(func1(L))

# %% ----------------------------------- FUNC2 ------------------------- #
'''func2: 20 marks

Write a function func2(words) that receives as input:
- words: a list of strings.

The function returns a dictionary where:
- each key is an integer N,
- the corresponding value is a list of words from the input that have that
  have exactly N unique characters; the list is sorted in ascending alphabetical order.

Example:
words = ['apple', 'pear', 'banana', 'tea', 'dog', 'ant']
func2(words)
output: {4: ['apple', 'pear'], 3: ['ant', 'banana', 'dog', 'tea']}
'''

def unique_ch(word):
    s = set()
    for ch in word:
        if ch not in s:
            s.add(ch)
    return len(s)

def func2(words):
    # your code goes here
    tuple_lst = []
    rd = dict()
    for word in words:
        tuple_lst.append((unique_ch(word), word))
    for t in tuple_lst:
        if t[0] not in rd:
            rd[t[0]] = list()
            rd[t[0]].append(str(t[1]))
        else:
            rd[t[0]].append(str(t[1]))
    for i in rd:
        rd[i].sort()
    return rd
    pass

# words = ['apple', 'pear', 'banana', 'tea', 'dog', 'ant']
# print(func2(words))
# words = ['programming', 'alternatives', 'representation', 'refraction', 'unknown']
# print(func2(words))
# words = ['aaaaaaa', 'bbbbbbbbaaaaaaaa', 'cba', 'ddccbbaa', 'retrospectivity', 'a']
# print(func2(words))
# words = ['coooooooooool', 'hhhhhhhhhheighhhht', 'zoooooooooooooo', 'hiiiiiiii']
# print(func2(words))

# %% ----------------------------------- FUNC3 ------------------------- #
'''func3: 20 marks

Write a function func3(int_list, Action) that receives as input:
- int_list: a list of integer values.
- Action: a dictionary with integer keys and values that are either 'a' (add) or 'r' (remove).

The function must modify the input list in place so that:
- For every key in Action:
    - If Action[value] is 'a', then value must be appended to the list;
    - If Action[value] is 'r', then all occurrences of value must be removed from the list.
Finally, the list must be sorted in descending order.
The function returns the number of elements removed from int_list.

Example:
int_list = [7, 3, 6, 5, 7]
Action = {2: 'a', 7: 'r', 4: 'a'}
func3(int_list, Action) returns 2 and after the calling, int_list is [6, 5, 4, 3, 2]
'''

def func3(int_list, Action):
    # your code goes here
    counter = 0
    excep = set()
    for j in Action:
        if Action[j] == 'r':
            while j in int_list:
                counter += 1
                int_list.remove(j)
            excep.add(j)            
        if Action[j] == 'a' and j not in excep:
            int_list.append(j)
            excep.add(j)
    int_list.sort(reverse=True)
    return counter
    pass



# int_list = [7, 3, 6, 5, 7]
# Action = {2: 'a', 7: 'r', 4: 'a'}
# print(func3(int_list, Action))
# print(int_list)
#
# int_list = [1, 1, 1, 2, 2, 2, 2]
# Action = {1: 'r', 2: 'r'}
# print(func3(int_list, Action))
# print(int_list)
#
# int_list = [3, 2, 1]
# Action = {1: 'r', 2: 'r', 3: 'r', 4: 'a', 5: 'a'}
# print(func3(int_list, Action))
# print(int_list)
#
# int_list = [0]
# Action = {1: 'a', 2: 'a', 3: 'a', 4: 'a', 0: 'r', 4: 'r'}
# print(func3(int_list, Action))
# print(int_list)

# %% ----------------------------------- FUNC4 ------------------------- #
'''func4: 20 marks

Write a function func4(pairs) that receives as input:
- pairs: a set of tuples, each of the form (int, string)

The function returns a list of pairs, sorted:

- by string length, descending;
- in case of a tie, by the string value, ascending;
- in case of a tie, by the int value, descending.

Note: to sort the list, you must use the key parameter in the sorted function
    and write an explicit key function using all elements of each triple.

Example:
pairs = {
    (2, "cat"),
    (2, "fish"),
    (1, "cat"),
    (2, "bat")
}
func4(pairs)
# output: [(2, "fish"), (2, "bat"), (2, "cat"), (1, "cat")]
'''

def func4(pairs):
    # your code goes here
    rlist = sorted(pairs, key = lambda x: [-len(x[1]), x[1], -x[0]])
    return rlist
    pass

# pairs = {
#     (2, "cat"),
#     (2, "fish"),
#     (1, "cat"),
#     (2, "bat")
# }
# print(func4(pairs))
#
# pairs = {
#     (5, "hello"),
#     (5, "gear"),
#     (5, "sunny"),
#     (6, "aero"),
#     (6, "bull"),
#     (6, "wheel")
# }
# print(func4(pairs))
#
# pairs = {
#     (3, "bat"),
#     (2, "bat"),
#     (1, "bat"),
#     (4, "bat")
# }
# print(func4(pairs))
#
# pairs = {
#     (1, "room"),
#     (1, "hello"),
#     (1, "house"),
#     (2, "sunny"),
#     (2, "funny")
# }
# print(func4(pairs))

# %% ----------------------------------- FUNC5 ------------------------- #
'''func5: 20 marks

Write a function func5(inputfilename, outputfilename) that receives as input
- inputfilename: a string representing the pathname of a text file,
- outputfilename: a string representing the pathname of a text file.

The inputfile contains several lines of text with words separated by
any number of spaces (' '), commas (','), periods ('.').

The function returns a dictionary where:
- the keys are the words found in inputfilename, all in lowercase;
- the corresponding values are lists of numbers, representing the line
numbers in the input file where the words were found (case-insensitive,
first line of the file is line 0).

Moreover, the function must write in each line of outputfilename
one of the words found in inputfilename in lowercase, followed by
a space (' '), followed by the line numbers where the word appeared in
the input file separated by spaces.
Words in the output file must be ordered in descending order, while
the line numbers must be in ascending order.

Example, if the content of inputfilname is:
cat tacos Coast
coast toast
Tacos

TOAST caT costa
cOast toast
    
func5(inputfilename, outputfilename) must return the dictionary
{'cat':[0,4], 'tacos':[0,2], 'coast':[0,1,5], 'toast':[1,4,5], 'costa':[4]}
and write the following in outputfilename:
toast 1 4 5
tacos 0 2
costa 4
coast 0 1 5
cat 0 4
'''

def lower_custom(word):
    rlist = []
    for ch in word:
        if ch.isalpha():
            rlist.append(ch.lower())
        else:
            rlist.append(ch)
    return "".join(rlist)


def func5(inputfilename, outputfilename):
    # your code goes here
    # read file
    with open(inputfilename, 'r') as inf:
        lines = inf.readlines()
    # process each line
    count = dict()
    for index in range(len(lines)):
        lines[index] = lines[index].replace(",", " ")
        lines[index] = lines[index].replace(".", " ")
        line_pd = lines[index].split()
        # process each word
        # index -> num of line
        for word in line_pd:
            word_ = lower_custom(word)
            if word_ not in count:
                count[word_] = list()
                count[word_].append(index)
            else:
                count[word_].append(index)
    # sort and process for ouf
    ouf_list = []
    for w in count:
        count[w].sort()
        ouf_list.append((w, count[w]))
    ouf_list = sorted(ouf_list, key= lambda x: x[0], reverse= True)
    print(ouf_list)
    # write
    with open(outputfilename, 'w') as ouf:
        for i in ouf_list:
            ouf.write(str(i[0]) + " ")
            for j in i[1]:
                ouf.write(str(j) + " ")
            ouf.write("\n")
    return count
    pass

# print(func5('func5/input_example_1.txt', 'func5/expected_output_1.txt'))
# print(func5('func5/input_example_2.txt', 'func5/expected_output_2.txt'))
# print(func5('func5/input_example_3.txt', 'func5/expected_output_3.txt'))
# print(func5('func5/input_example_4.txt', 'func5/expected_output_4.txt'))


###################################################################################
if __name__ == '__main__':
    # your tests go here
    print('*' * 50)
    print('You have to run grade.py if you want to debug with the automatic grader.')
    print('Otherwise you can insert here you code to test the functions but you have to write your own tests')
    print('*' * 50)
