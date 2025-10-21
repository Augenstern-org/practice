# -*- coding: utf-8 -*-
"""
Created on Tue Oct 21 11:29:34 2025

@author: Administrator
"""

def write_list_with_spaces(filename, alist):
    ''' Creates a new file named filename
    and writes all the strings of alist
    separated by exactly one whitespace '''
    with open(filename, 'w') as f:
        for string in alist:
            f.write(string)
            f.write(' ')
            #f.write(string+' ')