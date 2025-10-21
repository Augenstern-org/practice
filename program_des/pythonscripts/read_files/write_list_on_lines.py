# -*- coding: utf-8 -*-
"""
Created on Tue Oct 21 11:39:06 2025

@author: Administrator
"""

def write_list_on_lines(filename, alist):
    ''' Creates a new file named filename
    and writes all the strings of alist
    in a different line each. The lines
    must be ordered in ascending order'''
    with open(filename, 'w') as f:
        for string in sorted(alist):
#            f.write(string)
 #           f.write('\n')
            f.write(string+'\n')