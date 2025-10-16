def a():
    print('a')
    return 'a'

def b():
    print('b')
    a()
    return 'b'

def c():
    print('c')
    b()
    a()
    return 'c'
    
