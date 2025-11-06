# -*- coding: utf-8 -*-
import testlib
import isrecursive
import os
import sys
import tree
from testlib import my_print, COL, check_expected

############ check that you have renamed the file as program.py   ###########
if not os.path.isfile('program.py'):
    print('WARNING: Save program.empty.py as program.py\n'
          'ATTENZIONE: salvare program.vuoto.py con nome program.py')
    sys.exit(0)
#############################################################################

import program

#############################################################################
#### Use DEBUG=True to disable the recursion tests and enable the
#### stack trace: each error will produce a more verbose output
####
#### Mettete DEBUG=True per disattivare i test di ricorsione  e
#### fare debug delle funzioni più facilmente attivando stack trace
# DEBUG = True
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
#%% ---

def do_func1_tests(L, expected):
    res = program.func1(L)
    testlib.check_set(res, expected)
    return 5                 # peso di ciascun test (4 × 0.5 = 2)

# ---------- test 1 ----------------------------------------------------
def test_func1_1(run=True):
    '''
    L = [[4, 2, 6], [6, 3, 6], [2, 1, 6]]
    expected = {6}
    '''
    L = [[4, 2, 6], [6, 3, 6], [2, 1, 6]]
    expected = {6}
    return do_func1_tests(L, expected) if run else None

# ---------- test 2 ----------------------------------------------------
def test_func1_2(run=True):
    '''
    L = [[1, 2, 3, 4, 5], [2, 3, 4, 5], [3, 4, 5], [4, 5], [5]]
    expected = {5}
    '''
    L = [[1, 2, 3, 4, 5], [2, 3, 4, 5], [3, 4, 5], [4, 5], [5]]
    expected = {5}
    return do_func1_tests(L, expected) if run else None

# ---------- test 3 ----------------------------------------------------
def test_func1_3(run=True):
    '''
    L = [[20, 15, 10, 5, 0], [100, 105, 5, 200, 205, 5, 15], [5, 5, 5, 5, 15, 15, 15, -1]]
    expected = {5, 15}
    '''
    L = [[20, 15, 10, 5, 0], [100, 105, 5, 200, 205, 5, 15], [5, 5, 5, 5, 15, 15, 15, -1]]
    expected = {5, 15}
    return do_func1_tests(L, expected) if run else None

# ---------- test 4 ----------------------------------------------------
def test_func1_4(run=True):
    '''
    L = [[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -5], [5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5], [-5, -4, -3, -3, -2, -2, -2, -1, 0, 0]]
    expected = {-2, -5, -4, -3, -1}
    '''
    L = [[-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -5], [5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5], [-5, -4, -3, -3, -2, -2, -2, -1, 0, 0]]
    expected = {-2, -5, -4, -3, -1}
    return do_func1_tests(L, expected) if run else None


def do_func2_tests(L, expected):
    res = program.func2(L)
    testlib.check_dict(res, expected)
    return 5

def test_func2_1(run=True):
    '''
    L = ['apple', 'pear', 'banana', 'tea', 'dog', 'ant']
    expected = {4: ['apple', 'pear'], 3: ['ant', 'banana', 'dog', 'tea']}
    '''
    L = ['apple', 'pear', 'banana', 'tea', 'dog', 'ant']
    expected = {4: ['apple', 'pear'], 3: ['ant', 'banana', 'dog', 'tea']}
    return do_func2_tests(L, expected)

def test_func2_2(run=True):
    '''
    L = ['programming', 'alternatives', 'representation', 'refraction', 'unknown']
    expected = {8: ['programming'], 9: ['alternatives', 'refraction', 'representation'], 5: ['unknown']}
    '''
    L = ['programming', 'alternatives', 'representation', 'refraction', 'unknown']
    expected = {8: ['programming'], 9: ['alternatives', 'refraction', 'representation'], 5: ['unknown']}
    return do_func2_tests(L, expected)

def test_func2_3(run=True):
    '''
    L = ['aaaaaaa', 'bbbbbbbbaaaaaaaa', 'cba', 'ddccbbaa', 'retrospectivity', 'a']
    expected = {1: ['a', 'aaaaaaa'], 2: ['bbbbbbbbaaaaaaaa'], 3: ['cba'], 4: ['ddccbbaa'], 10: ['retrospectivity']}
    '''
    L = ['aaaaaaa', 'bbbbbbbbaaaaaaaa', 'cba', 'ddccbbaa', 'retrospectivity', 'a']
    expected = {1: ['a', 'aaaaaaa'], 2: ['bbbbbbbbaaaaaaaa'], 3: ['cba'], 4: ['ddccbbaa'], 10: ['retrospectivity']}
    return do_func2_tests(L, expected)

def test_func2_4(run=True):
    '''
    L = ['coooooooooool', 'hhhhhhhhhheighhhht', 'zoooooooooooooo', 'hiiiiiiii']
    expected = {3: ['coooooooooool'], 5: ['hhhhhhhhhheighhhht'], 2: ['hiiiiiiii', 'zoooooooooooooo']}
    '''
    L = ['coooooooooool', 'hhhhhhhhhheighhhht', 'zoooooooooooooo', 'hiiiiiiii']
    expected = {3: ['coooooooooool'], 5: ['hhhhhhhhhheighhhht'], 2: ['hiiiiiiii', 'zoooooooooooooo']}
    return do_func2_tests(L, expected)


def do_func3_tests(L, Action, expected_val, expected_L):
    res = program.func3(L, Action)
    testlib.check_val(res, expected_val)
    testlib.check_list(L, expected_L)
    return 5

def test_func3_1(run=True):
    '''
    L = [7, 3, 6, 5, 7]
    Action = {2: 'a', 7: 'r', 4: 'a'}
    expected_val = 2
    expected_L = [6, 5, 4, 3, 2]
    '''
    L = [7, 3, 6, 5, 7]
    Action = {2: 'a', 7: 'r', 4: 'a'}
    expected_val = 2
    expected_L = [6, 5, 4, 3, 2]
    return do_func3_tests(L, Action, expected_val, expected_L)

def test_func3_2(run=True):
    '''
    L = [1, 1, 1, 2, 2, 2, 2]
    Action = {1: 'r', 2: 'r'}
    expected_val = 7
    expected_L = []
    '''
    L = [1, 1, 1, 2, 2, 2, 2]
    Action = {1: 'r', 2: 'r'}
    expected_val = 7
    expected_L = []
    return do_func3_tests(L, Action, expected_val, expected_L)

def test_func3_3(run=True):
    '''
    L = [3, 2, 1]
    Action = {1: 'r', 2: 'r', 3: 'r', 4: 'a', 5: 'a'}
    expected_val = 3
    expected_L = [5, 4]
    '''
    L = [3, 2, 1]
    Action = {1: 'r', 2: 'r', 3: 'r', 4: 'a', 5: 'a'}
    expected_val = 3
    expected_L = [5, 4]
    return do_func3_tests(L, Action, expected_val, expected_L)

def test_func3_4(run=True):
    '''
    L = [0]
    Action = {1: 'a', 2: 'a', 3: 'a', 4: 'a', 0: 'r', 4: 'r'}
    expected_val = 1
    expected_L = [3, 2, 1]
    '''
    L = [0]
    Action = {1: 'a', 2: 'a', 3: 'a', 4: 'a', 0: 'r', 4: 'r'}
    expected_val = 1
    expected_L = [3, 2, 1]
    return do_func3_tests(L, Action, expected_val, expected_L)


def do_func4_tests(S, expected):
    res = program.func4(S)
    testlib.check_list(res, expected)
    return 5

def test_func4_1(run=True):
    '''
    S = {
    (2, "cat"),
    (2, "fish"),
    (1, "cat"),
    (2, "bat")
    }
    expected = [(2, 'fish'), (2, 'bat'), (2, 'cat'), (1, 'cat')]
    '''
    S = {
    (2, "cat"),
    (2, "fish"),
    (1, "cat"),
    (2, "bat")
    }
    expected = [(2, 'fish'), (2, 'bat'), (2, 'cat'), (1, 'cat')]
    return do_func4_tests(S, expected)

def test_func4_2(run=True):
    '''
    S = {
    (5, "hello"),
    (5, "gear"),
    (5, "sunny"),
    (6, "aero"),
    (6, "bull"),
    (6, "wheel")
    }
    expected = [(5, 'hello'), (5, 'sunny'), (6, 'wheel'), (6, 'aero'), (6, 'bull'), (5, 'gear')]
    '''
    S = {
    (5, "hello"),
    (5, "gear"),
    (5, "sunny"),
    (6, "aero"),
    (6, "bull"),
    (6, "wheel")
    }
    expected = [(5, 'hello'), (5, 'sunny'), (6, 'wheel'), (6, 'aero'), (6, 'bull'), (5, 'gear')]
    return do_func4_tests(S, expected)

def test_func4_3(run=True):
    '''
    S = {
    (3, "bat"),
    (2, "bat"),
    (1, "bat"),
    (4, "bat")
    }
    expected = [(4, 'bat'), (3, 'bat'), (2, 'bat'), (1, 'bat')]
    '''
    S = {
    (3, "bat"),
    (2, "bat"),
    (1, "bat"),
    (4, "bat")
    }
    expected = [(4, 'bat'), (3, 'bat'), (2, 'bat'), (1, 'bat')]
    return do_func4_tests(S, expected)

def test_func4_4(run=True):
    '''
    S = {
    (1, "room"),
    (1, "hello"),
    (1, "house"),
    (2, "sunny"),
    (2, "funny")
    }
    expected = [(2, 'funny'), (1, 'hello'), (1, 'house'), (2, 'sunny'), (1, 'room')]
    '''
    S = {
    (1, "room"),
    (1, "hello"),
    (1, "house"),
    (2, "sunny"),
    (2, "funny")
    }
    expected = [(2, 'funny'), (1, 'hello'), (1, 'house'), (2, 'sunny'), (1, 'room')]
    return do_func4_tests(S, expected)


# ----------------------------------- EX.1 ----------------------------------- #

def do_func5_tests(ID, expected):
    input_filename  = f'func5/input_example_{ID}.txt'
    output_filename = f'func5/your_output_{ID}.txt'
    expected_filename = f'func5/expected_output_{ID}.txt'
    res = program.func5(input_filename, output_filename)
    testlib.check_dict(res, expected)
    testlib.check_text_file(output_filename, expected_filename)
    return 5


def test_func5_1(run=True):
    '''
    input_filename = 'func5/input_example_1.txt'
    output_filename = 'func5/your_output_1.txt'
    expected_filename = 'func5/expected_output_1.txt'
    expected = {'cat': [0, 4], 'tacos': [0, 2], 'coast': [0, 1, 5], 'toast': [1, 4, 5], 'costa': [4]}
    '''
    ID = 1
    expected = {'cat': [0, 4], 'tacos': [0, 2], 'coast': [0, 1, 5], 'toast': [1, 4, 5], 'costa': [4]}
    return do_func5_tests(ID, expected)


def test_func5_2(run=True):
    '''
    input_filename = 'func5/input_example_2.txt'
    output_filename = 'func5/your_output_2.txt'
    expected_filename = 'func5/expected_output_2.txt'
    expected = 70
    '''
    ID = 2
    expected = {'repo': [0, 2, 3, 8, 10], 'rep0': [5, 7]}
    return do_func5_tests(ID, expected)


def test_func5_3(run=True):
    '''
    input_filename = 'func5/input_example_3.txt'
    output_filename = 'func5/your_output_3.txt'
    expected_filename = 'func5/expected_output_3.txt'
    expected = 520
    '''
    ID = 3
    expected = {'tool': [0, 2, 4, 6], 'case': [0, 2, 4, 6], 'tools': [0, 2, 4, 6]}
    return do_func5_tests(ID, expected)

def test_func5_4(run=True):
    '''
    input_filename = 'func5/input_example_4.txt'
    output_filename = 'func5/your_output_4.txt'
    expected_filename = 'func5/expected_output_4.txt'
    expected = 1700
    '''
    ID = 4
    expected = {'a': [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11], 'b': [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 'c': [0, 1, 2, 3, 4, 5, 6, 7, 8, 9], 'd': [0, 1, 2, 3, 4, 5, 6, 7, 8], 'e': [0, 1, 2, 3, 4, 5, 6, 7], 'f': [0, 1, 2, 3, 4, 5, 6], 'g': [0, 1, 2, 3, 4, 5], 'h': [0, 1, 2, 3, 4], 'i': [0, 1, 2, 3], 'j': [0, 1, 2], 'k': [0, 1], 'l': [0]}
    return do_func5_tests(ID, expected)



# ----------------------------------- EX.1 ----------------------------------- #
def do_test_ex1(input_tree, expected_tree, expected_value):
    if not DEBUG:
        try:
            isrecursive.decorate_module(program)
            program.ex1(input_tree)
        except isrecursive.RecursionDetectedError:
            pass
        else:
            raise Exception("Il programma non adotta un approccio ricorsivo / The function does not use recursion")
        finally:
            isrecursive.undecorate_module(program)

    val = program.ex1(input_tree)
    testlib.check_val(val, expected_value)
    testlib.check_val(input_tree.__str__(), expected_tree.__str__(), "L'albero modificato non è corretto / The modified tree is not correct")
    return 1.5


def test_ex1_1(run=True):
    input_tree = tree.BinaryTree.fromList(["", None, None])
    expected_tree = tree.BinaryTree.fromList(["", None, None])
    return do_test_ex1(input_tree, expected_tree, 0)


def test_ex1_2(run=True):
    input_tree = tree.BinaryTree.fromList(["", ["", None, None], ["", None, None]])
    expected_tree = tree.BinaryTree.fromList(["", ["*", None, None], ["*", None, None]])
    return do_test_ex1(input_tree, expected_tree, 1)

def test_ex1_3(run=True):
    input_tree = tree.BinaryTree.fromList(["", ["", ["", None, None], None], ["", None, ["", None, None]]])
    expected_tree = tree.BinaryTree.fromList(["", ["*", ["**", None, None], None], ["*", None, ["**", None, None]]])
    return do_test_ex1(input_tree, expected_tree, 2)

def test_ex1_4(run=True):
    L = ["", ["", ["", ["", None, ["", None, None]], ["", ["", None, None], ["", None, None]]], ["", ["", ["", ["", None, None], ["", None, None]], ["", ["", None, None], ["", None, None]]], ["", None, None]]], ["", None, ["", ["", ["", ["", None, None], ["", None, None]], ["", None, None]], ["", ["", None, None], None]]]]
    input_tree = tree.BinaryTree.fromList(L)
    expected_tree = tree.BinaryTree.fromList(['', ['*', ['**', ['***', None, ['****', None, None]], ['***', ['****', None, None], ['****', None, None]]], ['**', ['***', ['****', ['*****', None, None], ['*****', None, None]], ['****', ['*****', None, None], ['*****', None, None]]], ['***', None, None]]], ['*', None, ['**', ['***', ['****', ['*****', None, None], ['*****', None, None]], ['****', None, None]], ['***', ['****', None, None], None]]]])
    return do_test_ex1(input_tree, expected_tree, 5)
# ----------------------------------- EX. 2----------------------------------- #

def do_ex2_test(input_data, expected):
    if not DEBUG:
        try:
            isrecursive.decorate_module(program)
            program.ex2(input_data[0], input_data[1])
        except isrecursive.RecursionDetectedError:
            pass
        else:
            raise Exception("The program does not employ recursion / Il programma non adotta un approccio ricorsivo")
        finally:
            isrecursive.undecorate_module(program)

    res = program.ex2(input_data[0], input_data[1])
    if res != expected:
        my_print(f'''{'*'*50}\n[ERROR] Il valore ritornato non è corretto! / The returned value is incorrect!!\nReturned={res}, expected={expected}''')
        return 0
    return 1.5

def test_ex2_1(run=True):
    '''
    L = [['a', 'b'], ['c', 'e']]
    k = 1
    expected = ['ac', 'be']
    '''
    input_data = ([['a', 'b'], ['c', 'e']], 1)
    expected = ['ac', 'be']
    return do_ex2_test(input_data, expected)

def test_ex2_2(run=True):
    '''
    L = [['a'], ['b', 'c'], ['e'], ['f']]
    k = 2
    expected = ['abef', 'acef']
    '''
    input_data = ([['a'], ['b', 'c'], ['e'], ['f']], 2)
    expected = ['abef', 'acef']
    return do_ex2_test(input_data, expected)

def test_ex2_3(run=True):
    '''
    L = [['i'], ['o'], ['p', 'q']]
    k = 2
    expected = ['iop', 'ioq']
    '''
    input_data = ([['i'], ['o'], ['p', 'q']], 2)
    expected = ['iop', 'ioq']
    return do_ex2_test(input_data, expected)

def test_ex2_4(run=True):
    '''
    L = [['a'], ['b'], ['c'], ['d'], ['e']]
    k = 4
    expected = []
    '''
    input_data = ([['a'], ['b'], ['c'], ['d'], ['e']], 4)
    expected = []
    return do_ex2_test(input_data, expected)

################################################################################

tests = [
    # TO RUN ONLY SOME OF THE TESTS, comment any of the following entries
    # PER DISATTIVARE ALCUNI TEST, commentare gli elementi seguenti
    test_func1_1, test_func1_2, test_func1_3, test_func1_4,
    test_func2_1, test_func2_2, test_func2_3, test_func2_4,
    test_func3_1, test_func3_2, test_func3_3, test_func3_4,
    test_func4_1, test_func4_2, test_func4_3, test_func4_4,
    test_func5_1, test_func5_2, test_func5_3, test_func5_4,
    # test_ex1_1,  test_ex1_2, test_ex1_3, test_ex1_4,
    # test_ex2_1,    test_ex2_2, test_ex2_3, test_ex2_4,
    test_personal_data_entry,
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
