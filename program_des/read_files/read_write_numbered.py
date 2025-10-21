# -*- coding: utf-8 -*-
"""
Created on Tue Oct 21 11:54:51 2025

@author: Administrator
"""

def read_write_numbered(inputfile, outputfile):
    ''' Reads the content of inputfile, one line
    at the time and writes in output file
    each line with the line number added in
    front ('/* n */') 
    
    If the inputfile has
    
    Hello
    world
    
    the output file should be
    
    /* 1 */ Hello
    /* 2 */ world
    
    The function returns the number of lines
    written.
    '''
    