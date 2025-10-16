def a(x):
    print('in a with x =', x)
    if x > 0:
        return a(x-1)
    else:
        return 1
