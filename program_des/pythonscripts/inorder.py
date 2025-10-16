def inorder(x,y,z):
    ''' Returns true if the three numbers
are ordered from the smallest to the largest,
False, otherwise
   3 5 1 False
   4 1 6 False
   1 4 6 True
   1 1 4 True 
'''
    if x <= y and y <= z:
    # This is a comment
    # an alternative way is
    # if x <= y <= z:
        return True
    else:
        return False
    
