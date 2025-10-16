from is_leap import is_leap

def check_date(string):
    ''' A function that gets a string
and checks if it is a valid date in
the format dd/mm/yyyy, ignoring
leap years '''
    ''' Possible solution
- check if the month is within 1 <=m<=12
- if yes, determine the max day
 - check if the day is within 1 <=d<=md'''
    day = string[0:2]
    month = string[3:5]
    year = string[6:]
    if not(1<=int(month)<=12):
        return False
    maxday = 31
    if month in '04060911':
        maxday = 30
    elif month == '02':
        maxday = 28
        if is_leap(int(year)):
            maxday = 29
    if not(1<=int(day)<=maxday):
        return False
    else:
        return True
    






    
    
