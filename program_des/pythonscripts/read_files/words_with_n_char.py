# -*- coding: utf-8 -*-
"""
Created on Mon Oct 20 15:35:09 2025

@author: Administrator
"""

def words_with_n_char(filename, char, n):
    ''' Return a list with all the words in filename
        which have the characater char occuring exactly
        n times '''
        
    'peach, apple, pinapple, kiwi, pear'
    with open(filename) as f:
        text = f.read()
        words = text.split()
    result = []
    for word in words:
        if word.count(char) ==n:
            result.append(word)
    return result
            
            
            