# -*- coding: utf-8 -*-
import testlib
import isrecursive
import os
import sys
import tree
from testlib import my_print, COL, check_expected

############ check that you have renamed the file as program.py   ###########
if not os.path.isfile('program.py'):
    print('WARNING: Save program.empty.py as program.py')
    sys.exit(0)
#############################################################################

import program

#############################################################################
#### Use DEBUG=True to disable the recursion tests and enable the
#### stack trace: each error will produce a more verbose output
####
#DEBUG = True
DEBUG = False
#############################################################################

################################################################################
# ------- THE SOURCE CODE FROM THIS POINT FORWARD IS FOR TESTING ONLY -------- #

# ----- The use of the following functions in your program is forbidden ------ #
################################################################################

def test_personal_data_entry(run=True):
    if 'name' in program.__dict__:
        assert program.name       != 'NAME', f"{COL['YELLOW']}ERROR: Please assign the 'name' variable with YOUR NAME in program.py{COL['RST']}"
        assert program.surname    != 'SURNAME', f"{COL['YELLOW']}ERROR: Please assign the 'surname' variable with YOUR SURNAME in program.py{COL['RST']}"
        assert program.student_id != 'MATRICULATION NUMBER', f"{COL['YELLOW']}ERROR: Please assign the 'student_id' variable with YOUR MATRICULATION NUMBER in program.py{COL['RST']}"
        print(f'{COL["GREEN"]}Student info: {program.name} {program.surname} {program.student_id}{COL["RST"]}')
    else:
        assert program.nome      != 'NOME', f"{COL['YELLOW']}ERRORE: Indica il tuo NOME in program.py{COL['RST']}"
        assert program.cognome   != 'COGNOME', f"{COL['YELLOW']}ERRORE: Indica il tuo COGNOME in program.py{COL['RST']}"
        assert program.matricola != 'MATRICOLA', f"{COL['YELLOW']}ERRORE: Indica il tuo NUMERO DI MATRICOLA in program.py{COL['RST']}"
        print(f'{COL["GREEN"]}Informazioni studente: {program.nome} {program.cognome} {program.matricola}{COL["RST"]}')
    return 1e-9

def add_docstring(f, local):
    S = ''
    if 'run' in local: del local['run']
    for key, val in local.items():
        S += f'\n{key} = {val}'
    f.__doc__ = S


###############################################################################

def do_func1_tests(D, expected):
    res = program.func1(D)
    testlib.check_list(res, expected)
    return 0.5                 # peso di ciascun test (4 × 0.5 = 2)

# ---------- test 1 ----------------------------------------------------
def test_func1_1(run=True):
    '''
    D = {2: ['s', 'u', 'e'], 3: ['q', 'a']}
    expected = ['uu', 'ss', 'qqq', 'ee', 'aaa']
    '''
    D = {2: ['s', 'u', 'e'], 3: ['q', 'a']}
    expected = ['uu', 'ss', 'qqq', 'ee', 'aaa']
    return do_func1_tests(D, expected) if run else None

# ---------- test 2 ----------------------------------------------------
def test_func1_2(run=True):
    '''
    D = {1: ['b', 'c'], 4: ['a']}
    expected = ['c', 'b', 'aaaa']
    '''
    D = {1: ['b', 'c'], 4: ['a']}
    expected = ['c', 'b', 'aaaa']
    return do_func1_tests(D, expected) if run else None

# ---------- test 3 ----------------------------------------------------
def test_func1_3(run=True):
    '''
    D = {3: ['x', 'z'], 2: ['y', 'y']}
    expected = ['zzz', 'yy', 'yy', 'xxx']
    '''
    D = {3: ['x', 'z'], 2: ['y', 'y']}
    expected = ['zzz', 'yy', 'yy', 'xxx']
    return do_func1_tests(D, expected) if run else None

# ---------- test 4 ----------------------------------------------------
def test_func1_4(run=True):
    '''
    D = {
        5: ['d', 'd'],            # due blocchi da 5 'd'
        3: ['a', 'b', 'b', 'c'],  # un 'a', due 'b', un 'c'
        2: ['z', 'z', 'x']        # due 'z', un 'x'
    }
    expected = [
        'zz', 'zz', 'xx',         # da N = 2
        'ddddd', 'ddddd',         # da N = 5
        'ccc',                    # da N = 3
        'bbb', 'bbb',             # duplicati da N = 3
        'aaa'                     # da N = 3
    ]
    '''
    D = {
        5: ['d', 'd'],
        3: ['a', 'b', 'b', 'c'],
        2: ['z', 'z', 'x']
    }
    expected = [
        'zz', 'zz', 'xx',
        'ddddd', 'ddddd',
        'ccc',
        'bbb', 'bbb',
        'aaa'
    ]
    return do_func1_tests(D, expected) if run else None


def do_func2_tests(L, expected):
    res = program.func2(L)
    testlib.check_list(res, expected)
    return 0.5

def test_func2_1(run=True):
    '''
    L = [ [[]], [], [[[]]], [[]], [[[[]]]], [], [[[]]] ]
    expected = [1, 0, 2, 1, 3, 0, 2]
    '''
    L = [ [[]], [], [[[]]], [[]], [[[[]]]], [], [[[]]] ]
    expected = [1, 0, 2, 1, 3, 0, 2]
    return do_func2_tests(L, expected)

def test_func2_2(run=True):
    '''
    L = [ [[[[[]]]]], [], [[[]]], [[[]]], [[[[[[]]]]]] ]
    expected = [4, 0, 2, 2, 5]
    '''
    L = [
        [[[[[]]]]],   # 4 livelli
        [],           # 0 livelli
        [[[]]],       # 2 livelli
        [[[]]],       # 2 livelli
        [[[[[[]]]]]]  # 5 livelli
        ]
    expected = [4, 0, 2, 2, 5]
    return do_func2_tests(L, expected)

def test_func2_3(run=True):
    '''
    L = [ [], [[[]]], [[[]]], [[[[[[]]]]]], [[[]]] ]
    expected = [0, 2, 2, 5, 2]
    '''
    L = [
        [],
        [[[]]],
        [[[]]],
        [[[[[[]]]]]],
        [[[]]]
        ]
    expected = [0, 2, 2, 5, 2]
    return do_func2_tests(L, expected)

def test_func2_4(run=True):
    '''
    L = [ [], [[]], [[[]]], [[[[]]]], [[[[[]]]]] ]
    expected = [0, 1, 2, 3, 4]
    '''
    L = [
        [],
        [[]],
        [[[]]],
        [[[[]]]],
        [[[[[]]]]]
        ]
    expected = [0, 1, 2, 3, 4]
    return do_func2_tests(L, expected)


def do_func3_tests(S, expected):
    res = program.func3(S)
    testlib.check_val(res, expected)
    return 0.5

def test_func3_1(run=True):
    '''
    S = "Brad,ALIce, keVin,  oscar, Dana,   UMA,ian, Zoe"
    expected = ['ALIce', 'ian', 'oscar', 'UMA']
    '''
    S = "Brad,ALIce, keVin,  oscar, Dana,   UMA,ian, Zoe"
    expected = ['ALIce', 'ian', 'oscar', 'UMA']
    return do_func3_tests(S, expected)

def test_func3_2(run=True):
    '''
    S = "apple, Egg, orange, banana, Umbrella, Ice"
    expected = ['apple', 'Egg', 'Ice', 'orange', 'Umbrella']
    '''
    S = "apple, Egg, orange, banana, Umbrella, Ice"
    expected = ['apple', 'Egg', 'Ice', 'orange', 'Umbrella']
    return do_func3_tests(S, expected)

def test_func3_3(run=True):
    '''
    S = "Zoo, car, Dog, tree"
    expected = []
    '''
    S = "Zoo, car, Dog, tree"
    expected = []
    return do_func3_tests(S, expected)

def test_func3_4(run=True):
    '''
    S = "Eagle, igloo,   Octopus, Uranus, ant, Bee"
    expected = ['ant', 'Eagle', 'igloo', 'Octopus', 'Uranus']
    '''
    S = "Eagle, igloo,   Octopus, Uranus, ant, Bee"
    expected = ['ant', 'Eagle', 'igloo', 'Octopus', 'Uranus']
    return do_func3_tests(S, expected)



# ----------------------------------- EX.1 ----------------------------------- #

def do_func4_tests(ID, expected):
    input_filename  = f'func4/in_test{ID}.txt'
    output_filename = f'func4/out_test{ID}.txt'
    expected_filename = f'func4/exp_test{ID}.txt'
    res = program.func4(input_filename, output_filename)
    testlib.check_dict(res, expected)
    testlib.check_text_file(output_filename, expected_filename)
    return 1.5


def test_func4_1(run=True):
    '''
    input_filename = 'func4/in_test1.txt'
    output_filename = 'func4/out_test1.txt'
    expected_filename = 'func4/exp_test1.txt'
    expected = 12
    '''
    ID = 1
    expected = 12
    return do_func4_tests(ID, expected)


def test_func4_2(run=True):
    '''
    input_filename = 'func4/in_test2.txt'
    output_filename = 'func4/out_test2.txt'
    expected_filename = 'func4/exp_test2.txt'
    expected = 70
    '''
    ID = 2
    expected = 70
    return do_func4_tests(ID, expected)


def test_func4_3(run=True):
    '''
    input_filename = 'func4/in_test3.txt'
    output_filename = 'func4/out_test3.txt'
    expected_filename = 'func4/exp_test3.txt'
    expected = 520
    '''
    ID = 3
    expected = 520
    return do_func4_tests(ID, expected)

def test_func4_4(run=True):
    '''
    input_filename = 'func4/in_test4.txt'
    output_filename = 'func4/out_test4.txt'
    expected_filename = 'func4/exp_test4.txt'
    expected = 1700
    '''
    ID = 4
    expected = 1700
    return do_func4_tests(ID, expected)



################################################################################

tests = [
    # TO RUN ONLY SOME OF THE TESTS, comment any of the following entries
    test_func1_1, test_func1_2, test_func1_3, test_func1_4,
    test_func2_1, test_func2_2, test_func2_3, test_func2_4,
    test_func3_1, test_func3_2, test_func3_3, test_func3_4,
    test_func4_1, test_func4_2, test_func4_3, test_func4_4,
    test_personal_data_entry,
]


if __name__ == '__main__':
    if test_personal_data_entry() < 0:
        print(f"{COL['RED']}PERSONAL INFO MISSING. PLEASE FILL THE INITIAL VARS WITH YOUR NAME SURNAME AND STUDENT_ID{COL['RST']}")
        sys.exit()
    check_expected()
    testlib.runtests(   tests,
                        verbose=True,
                        logfile='grade.csv',
                        stack_trace=DEBUG)
    testlib.check_exam_constraints()
    if 'matricola' in program.__dict__:
        print(f"{COL['GREEN']}Nome: {program.nome}\nCognome: {program.cognome}\nMatricola: {program.matricola}{COL['RST']}")
    elif 'student_id' in program.__dict__:
        print(f"{COL['GREEN']}Name: {program.name}\nSurname: {program.surname}\nStudentID: {program.student_id}{COL['RST']}")
    else:
        print('we should not arrive here the  matricola/student ID variable is not present in program.py')
################################################################################
