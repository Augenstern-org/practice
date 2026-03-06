# -*- coding: utf-8 -*-
import testlib
import os
import sys
from testlib import my_print, COL, check_expected

############ check that you have renamed the file as program.py   ###########
if not os.path.isfile('program.py'):
    print('WARNING: You have to rename the program.empty.py!!!\n\
Check your working directory or the correctness of the filename.')
    sys.exit(0)
#############################################################################

import program

#############################################################################
#### Use DEBUG=True to disable the recursion tests and enable the
#### stack trace: each error will produce a more verbose output
####
#### Mettete DEBUG=True per disattivare i test di ricorsione  e
#### fare debug delle funzioni più facilmente attivando stack trace
DEBUG = True
DEBUG = False
#############################################################################

################################################################################
# ------- THE SOURCE CODE FROM THIS POINT FORWARD IS FOR TESTING ONLY -------- #

# ----- The use of the following functions in your program is forbidden ------ #
# ---------------------------------------------------------------------------- #
# --- IL CODICE SORGENTE DI SEGUITO È ESCLUSIVAMENTE PER EFFETTUARE I TEST --- #
# ------- L'uso delle funzioni seguenti nel vostro programma è vietato --------#
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

def do_func1_tests(int_list, m, n, expected):
    outfile = f'func1/out{m}{n}.txt'
    expfile = f'func1/exp{m}{n}.txt'
    res = program.func1(int_list, m, n, outfile)
    if res == None:
        raise testlib.NotImplemented
    testlib.check_list(res, expected)
    testlib.check_text_file(outfile, expfile)
    return 5


def test_func1_1(run=True):
    '''
    int_list = [16, 14, 10, 4, 2, 1, 12]
    m = 4
    n = 8
    expected = [12, 16]
    '''
    int_list = [16, 14, 10, 4, 2, 1, 12]
    m = 4
    n = 8
    expected = [12, 16]
    return do_func1_tests(int_list, m, n, expected)

def test_func1_2(run=True):
    '''
    int_list = [-5, 4, 5, 10, 3, -1, 2, 12, 10, 11, 10]
    m = 5
    n = 0
    expected = [5, 10, 10, 10]
    '''
    int_list = [-5, 4, 5, 10, 3, -1, 2, 12, 10, 11, 10]
    m = 5
    n = 0
    expected = [5, 10, 10, 10]
    return do_func1_tests(int_list, m, n, expected)

def test_func1_3(run=True):
    '''
    int_list = [728, 760, 519, 879, 486, 324, 252, 182, 439, 875, 724, 512, 391, 167, 68, 971, 713, 947, 445, 992]
    m = 5
    n = 500
    expected = [728, 760, 519, 879, 486, 324, 252, 182, 439, 876, 724, 512, 391, 167, 68, 971, 713, 947, 445, 992]
    '''
    int_list = [728, 760, 519, 879, 486, 324, 252, 182, 439, 875, 724, 512, 391, 167, 68, 971, 713, 947, 445, 992]
    m = 5
    n = 500
    expected = [760, 875]
    return do_func1_tests(int_list, m, n, expected)

def test_func1_4(run=True):
    '''
    int_list = [-78, 10, 76, 82, -27, -39, -65, -19, 74, 18, 20, -25, -38, -71, -52, -49, -69, 21, -27, 58, 20]
    m = 2
    n = 19
    expected =  [20, 20, 58, 74, 76, 82]
    '''
    int_list = [-78, 10, 76, 82, -27, -39, -65, -19, 74, 18, 20, -25, -38, -71, -52, -49, -69, 21, -27, 58, 20]
    m = 2
    n = 19
    expected =  [20, 20, 58, 74, 76, 82]
    return do_func1_tests(int_list, m, n, expected)


def do_func2_tests(namefile, expected):
    res = program.func2(namefile)
    if res == None:
        raise testlib.NotImplemented
    testlib.check_val(res, expected)
    return 5


def test_func2_1(run=True):
    '''
    namefile = 'func2/in01.txt'
    expected = 100
    '''
    namefile = 'func2/in01.txt'
    expected = 100
    return do_func2_tests(namefile, expected)

def test_func2_2(run=True):
    '''
    namefile = 'func2/in02.txt'
    expected = 5966
    '''
    namefile = 'func2/in02.txt'
    expected = 5966
    return do_func2_tests(namefile, expected)

def test_func2_3(run=True):
    '''
    namefile = 'func2/in03.txt'
    expected = 121
    '''
    namefile = 'func2/in03.txt'
    expected = 121
    return do_func2_tests(namefile, expected)

def test_func2_4(run=True):
    '''
    namefile = 'func2/in04.txt'
    expected = 2000
    '''
    namefile = 'func2/in04.txt'
    expected = 2000
    return do_func2_tests(namefile, expected)

def do_func3_tests(L0, L1, expected):
    res = program.func3(L0, L1)
    if res == None:
        raise testlib.NotImplemented
    testlib.check_val(res, expected)
    return 5

def test_func3_1(run=True):
    '''
    L0 = ['ab', 'o o']
    L1 = [2, 3]
    expected = "ababo oo oo o"
    '''
    L0 = ['ab', 'o o']
    L1 = [2, 3]
    expected = "ababo oo oo o"
    return do_func3_tests(L0, L1, expected)

def test_func3_2(run=True):
    '''
    L0 = ['quick', 'brow', 'fox']
    L1 = [2, 0, 2]
    expected = "quickquickfoxfox"
    '''
    L0 = ['quick', 'brow', 'fox']
    L1 = [2, 0, 2]
    expected = "quickquickfoxfox"
    return do_func3_tests(L0, L1, expected)

def test_func3_3(run=True):
    '''
    L0 = ['h', 'e', 'l', 'o']
    L1 = [1, 1, 2, 1]
    expected = "hello"
    '''
    L0 = ['h', 'e', 'l', 'o']
    L1 = [1, 1, 2, 1]
    expected = "hello"
    return do_func3_tests(L0, L1, expected)

def test_func3_4(run=True):
    '''
    L0 = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
    L1 = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    expected = "bccdddeeeefffffgggggghhhhhhhiiiiiiii"
    '''
    L0 = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
    L1 = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    expected = "bccdddeeeefffffgggggghhhhhhhiiiiiiii"
    return do_func3_tests(L0, L1, expected)

def do_func4_tests(ID, expected):
    output_filename = f'func4/out0{ID}.txt'
    input_filename = f'func4/in0{ID}.txt'
    expected_filename = f'func4/exp0{ID}.txt'
    res = program.func4(input_filename, output_filename)
    if res == None:
        raise testlib.NotImplemented()
    testlib.check_val(res, expected)
    testlib.check_text_file(output_filename, expected_filename)
    return 10


def test_func4_1(run=True):
    '''
    func4 -> ID = 1
    '''
    ID = 1
    expected = 120.0
    return do_func4_tests(ID, expected)

def test_func4_2(run=True):
    '''
    func4 -> 2
    '''
    ID = 2
    expected = 4620.0
    return do_func4_tests(ID, expected)

def test_func4_3(run=True):
    '''
    func4 -> 3
    '''
    ID = 3
    expected = 45.25
    return do_func4_tests(ID, expected)

def test_func4_4(run=True):
    '''
    func4 -> 4
    '''
    ID = 4
    expected = 29.18
    return do_func4_tests(ID, expected)


################################################################################

tests = [
    # TO RUN ONLY SOME OF THE TESTS, comment any of the following entries
    # PER DISATTIVARE ALCUNI TEST, commentare gli elementi seguenti
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
