def valid():
    print("\n   The date and it's format is valid. \n")
    return 1


def invalid():
    print("\n   Invalid Input! \n")
    return 0


def checkDate( input_date ):
    # the format is dd/mm/yyyy
    # init
    is_valid = 0
    # basic check (length?)
    if (len(input_date) != 10):
        return invalid()
    # (non-int?)
    try:
        dd = int(input_date[0]+input_date[1])
        mm = int(input_date[3]+input_date[4])
        yy = int(input_date[6]+input_date[7]+input_date[8]+input_date[9])
    except ValueError:
        print("Trying to convert the strings to integers.")
        return invalid()
    else:
        # dd mm and yyyy check
        if input_date[2] != input_date[5] or input_date[2] != "/":
            if input_date[2] == input_date[5] and input_date[2] == ".":
                print('Please use "/" instead of "."')
                return invalid()
            else:
                return invalid()
        if (dd <= 0 or yy <= 0 or mm <= 0 or mm > 12):
            return invalid()
        #
        l_mm = [4,6,9,11]
        b_mm = [1,3,5,7,8,10,12]
        # dd check (explicit)
        is_dd_valid = 0
        if(mm in(l_mm) and dd <= 30):
            is_dd_valid = 1
        if(mm in(b_mm) and dd <= 31):
            is_dd_valid = 1
        if(yy % 4 == 0 and yy % 100 != 0 or yy % 400 == 0):
            if(mm == 2 and dd <= 29):
                is_dd_valid = 1
        if(mm == 2 and dd <= 28):
            is_dd_valid = 1
        # output
        if(is_dd_valid):
            return valid()
        else:
            return invalid()
        return is_valid


is_run = True
print('\n################### DATE-CHECKER ###################\n','Press "e" to exit.\n')
while(is_run):
    date_to_check = input("Type the date:(dd/mm/yyyy)\n")
    if(date_to_check == "e"): break
    checkDate(date_to_check)
