# -*- coding: utf-8 -*-
import testlib
import os
import sys
from testlib import my_print, COL, check_expected

############ check that you have renamed the file as program.py   ###########
if not os.path.isfile('program.py'):
    print('WARNING: You have to rename the program.empty.py!!!\n\
         Please save it as program.py.')
    sys.exit(0)
#############################################################################

import program

#############################################################################
#### Use DEBUG=True to disable the recursion tests and enable the
#### stack trace: each error will produce a more verbose output
DEBUG = True
DEBUG = False
#############################################################################

################################################################################
# ------- THE SOURCE CODE FROM THIS POINT FORWARD IS FOR TESTING ONLY -------- #

# ----- The use of the following functions in your program is forbidden ------ #
################################################################################

def test_personal_data_entry(run=True):
    if program.name== 'NAME': print(f"{COL['YELLOW']}ERROR: Please assign the 'name' variable with YOUR NAME in program.py{COL['RST']}")
    elif program.surname == 'SURNAME': print(f"{COL['YELLOW']}ERROR: Please assign the 'surname' variable with YOUR SURNAME in program.py{COL['RST']}")
    elif program.student_id == 'MATRICULATION NUMBER': print(f"{COL['YELLOW']}ERROR: Please assign the 'student_id' variable with YOUR MATRICULATION NUMBER in program.py{COL['RST']}")
    else:
        print(f'{COL["GREEN"]}Student info: {program.name} {program.surname} {program.student_id}{COL["RST"]}')
        return True
    sys.exit(0)

def add_docstring(f, local):
    S = ''
    if 'run' in local: del local['run']
    for key, val in local.items():
        S += f'\n{key} = {val}'
    f.__doc__ = S


###############################################################################

def do_func1_tests(int_list, ID, expected):
    output_filename = f'txt/out1_0{ID}.txt'
    expected_filename = f'txt/exp1_0{ID}.txt'
    res = program.func1(int_list, output_filename)
    testlib.check_text_file(output_filename, expected_filename)
    if res != expected:
        testlib.check_list(res, expected)
        my_print(f'''{'*'*50}\n[ERROR] The returned value is incorrect!''')
        my_print(f'''Returned={res}\nexpected={expected}.\n{'*'*50}''')
        return 0
    return 5


def test_func1_1(run=True):
    '''
    int_list = [1, 2, 3, 4, 5]
    expected = [15, 14, 12, 9, 5]
    '''
    int_list = [1, 2, 3, 4, 5]
    expected = [15, 14, 12, 9, 5]
    return do_func1_tests(int_list, 1,  expected)

def test_func1_2(run=True):
    '''
    int_list = [-5, 4, 5, 10, 3, -1, 2, 12, 10, 11, 10]
    m = 5
    n = 0
    expected = [61, 66, 62, 57, 47, 44, 45, 43, 31, 21, 10]
    '''
    int_list = [-5, 4, 5, 10, 3, -1, 2, 12, 10, 11, 10]
    expected = [61, 66, 62, 57, 47, 44, 45, 43, 31, 21, 10]
    return do_func1_tests(int_list, 2, expected)

def test_func1_3(run=True):
    '''
    int_list = [-19, 74, 18, 20, -25, -38, -71, -52]
    m = 0
    n = 5
    expected = [-93, -74, -148, -166, -186, -161, -123, -52]
    '''
    int_list = [-19, 74, 18, 20, -25, -38, -71, -52]
    expected = [-93, -74, -148, -166, -186, -161, -123, -52]
    return do_func1_tests(int_list, 3, expected)

def test_func1_4(run=True):
    '''
    int_list = [-78, 10, 76, 82, -27, -39, -65, -19, 74, 18, 20, -25, -38, -71, -52, -49, -69, 21, -27, 58, 20]
    m = 2
    n = 19
    expected =  [-180, -102, -112, -188, -270, -243, -204, -139, -120, -194, -212, -232, -207, -169, -98, -46, 3, 72, 51, 78, 20]
    '''
    int_list = [-78, 10, 76, 82, -27, -39, -65, -19, 74, 18, 20, -25, -38, -71, -52, -49, -69, 21, -27, 58, 20]
    expected =  [-180, -102, -112, -188, -270, -243, -204, -139, -120, -194, -212, -232, -207, -169, -98, -46, 3, 72, 51, 78, 20]
    return do_func1_tests(int_list, 4, expected)


def do_func2_tests(str1, str2, expected):
    res = program.func2(str1, str2)
    if res == None:
        raise testlib.NotImplemented
    testlib.check_val(res, expected)
    return 5


def test_func2_1(run=True):
    '''
    str1 = 'plane'
    str2 = 'react'
    expected = 'PEACE'
    '''
    str1 = 'plane'
    str2 = 'react'
    expected = 'PEACE'
    return do_func2_tests(str1, str2, expected)

def test_func2_2(run=True):
    '''
    str1 = 'staircases'
    str2 = 'granulates'
    expected = 'GRAIRCASES'
    '''
    str1 = 'staircases'
    str2 = 'granulates'
    expected = 'GRAIRCASES'
    return do_func2_tests(str1, str2, expected)

def test_func2_3(run=True):
    '''
    str1 = 'infatuation'
    str2 = 'intangibles'
    expected = 'INFANGABIEN'
    '''
    str1 = 'infatuation'
    str2 = 'intangibles'
    expected = 'INFANGABIEN'
    return do_func2_tests(str1, str2, expected)

def test_func2_4(run=True):
    '''
    str1 = 'deliberately',
    str2 = 'reproductive'
    expected = 'DELIBDRATELE'
    '''
    str1 = 'deliberately'
    str2 = 'reproductive'
    expected = 'DELIBDRATELE'
    return do_func2_tests(str1, str2, expected)


def do_func3_tests(ID, expected):
    output_filename = f'txt/out_0{ID}.txt'
    input_filename = f'txt/in_0{ID}.txt'
    expected_filename = f'txt/exp_0{ID}.txt'
    res = program.func3(input_filename, output_filename)
    testlib.check_text_file(output_filename, expected_filename)
    if res != expected:
        my_print(f'''{'*'*50}\n[ERROR] The returned value is incorrect!''')
        my_print(f'''Returned={res}\nexpected={expected}.\n{'*'*50}''')
        return 0
    return 5

def test_func3_1(run=True):
    '''
    ID = 1
    expected = 'cat'
    '''
    ID = 1
    expected = 'cat'
    return do_func3_tests(ID, expected)

def test_func3_2(run=True):
    '''
    ID = 2
    expected = 'ABSurDLy'
    '''
    ID = 2
    expected = 'ABSurDLy'
    return do_func3_tests(ID, expected)

def test_func3_3(run=True):
    '''
    ID = 3
    expected = 'nOGGINS😌😌'
    '''
    ID = 3
    expected = 'nOGGINS😌😌'
    return do_func3_tests(ID, expected)

def test_func3_4(run=True):
    '''
    ID = 4
    expected = 'più'
    '''
    ID = 4
    expected = 'più'
    return do_func3_tests(ID, expected)

def do_func4_tests(list_a, list_b, expected):
    res = program.func4(list_a, list_b)
    if res == None:
        raise testlib.NotImplemented()
    testlib.check_val(res, expected)
    return 10


def test_func4_1(run=True):
    '''
    list_A = ["flash", "ColA", "USED", "lazer"]
    list_B = ["Rabit", "HELIOS", "trick", "suPER"]
    expected = ['a', 'lo', '', 'er']
    '''
    list_A = ["flash", "ColA", "USED", "lazer"]
    list_B = ["Rabit", "HELIOS", "trick", "suPER"]
    expected = ['a', 'lo', '', 'er']
    return do_func4_tests(list_A, list_B, expected)

def test_func4_2(run=True):
    '''
    list_A = ["RAM", "rom", "JaM", "leAP", "star"]
    list_B = ["", "aBcDeFgH", "aBcDeFgH", "aBcDeFgH", "aBcDeFgH"]
    expected = ['', '', 'a', 'ae', 'a']
    '''
    list_A = ["RAM", "rom", "JaM", "leAP", "star"]
    list_B = ["", "aBcDeFgH", "aBcDeFgH", "aBcDeFgH", "aBcDeFgH"]
    expected = ['', '', 'a', 'ae', 'a']
    return do_func4_tests(list_A, list_B, expected)

def test_func4_3(run=True):
    '''
    list_A = ["abcdefghijklmnopqrstuwxyz", "abcdefghijklmnopqrstuwxyz"]
    list_B = ["ZYXWUTSRQPONMLKJIHGFEDCBA", "zyxwutsrqponmlkjihgfedcba"]
    expected = ['abcdefghijklmnopqrstuwxyz', 'abcdefghijklmnopqrstuwxyz']
    '''
    list_A = ["abcdefghijklmnopqrstuwxyz", "abcdefghijklmnopqrstuwxyz"]
    list_B = ["ZYXWUTSRQPONMLKJIHGFEDCBA", "zyxwutsrqponmlkjihgfedcba"]
    expected = ['abcdefghijklmnopqrstuwxyz', 'abcdefghijklmnopqrstuwxyz']
    return do_func4_tests(list_A, list_B, expected)

def test_func4_4(run=True):
    '''
    list_A = ["catode", "dermatoglyphics", "uncopyrightable"]
    list_B = ["ZYXWUTSRQPONMLKJIHGFEDCBA", "zyxwutsrqponmlkjihgfedcba", "zyxwutsrqponmlkjihgfedcba"]
    expected = ['acdeot', 'acdeghilmoprsty', 'abceghilnoprtuy']
    '''
    list_A = ["catode", "dermatoglyphics", "uncopyrightable"]
    list_B = ["ZYXWUTSRQPONMLKJIHGFEDCBA", "zyxwutsrqponmlkjihgfedcba", "zyxwutsrqponmlkjihgfedcba"]
    expected = ['acdeot', 'acdeghilmoprsty', 'abceghilnoprtuy']
    return do_func4_tests(list_A, list_B, expected)


################################################################################

tests = [
    # TO RUN ONLY SOME OF THE TESTS, comment any of the following entries
    test_func1_1, test_func1_2, test_func1_3, test_func1_4,
    test_func2_1, test_func2_2, test_func2_3, test_func2_4,
    test_func3_1, test_func3_2, test_func3_3, test_func3_4,
    test_func4_1, test_func4_2, test_func4_3, test_func4_4,
]


if __name__ == '__main__':
    if not test_personal_data_entry():
        print(f"{COL['RED']}PERSONAL INFO MISSING. PLEASE FILL THE INITIAL VARS WITH YOUR NAME SURNAME AND STUDENT_ID{COL['RST']}")
        sys.exit()
    check_expected()
    testlib.runtests(   tests,
                        verbose=True,
                        logfile='grade.csv',
                        stack_trace=DEBUG)
    #testlib.check_exam_constraints()
    if 'matricola' in program.__dict__:
        print(f"{COL['GREEN']}Nome: {program.nome}\nCognome: {program.cognome}\nMatricola: {program.matricola}{COL['RST']}")
    elif 'student_id' in program.__dict__:
        print(f"{COL['GREEN']}Name: {program.name}\nSurname: {program.surname}\nStudentID: {program.student_id}{COL['RST']}")
    else:
        print('we should not arrive here the  matricola/student ID variable is not present in program.py')
################################################################################
