def is_leap(year):
    ''' A function that returns true
if the year is leap. '''
    if year % 400 == 0:
        return True
    if year % 100 == 0:
        return False
    if year % 4 == 0:
        return True
    else:
        return False
