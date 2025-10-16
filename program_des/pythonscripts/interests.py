def new_balance_20years(balance, rate):
    years = 0
    print('Balance at the beginning:', balance)
    while years < 20:
        interest = balance * rate
        balance = balance + interest
        print('Balance after', years, 'year:', round(balance, 2))
        years = years+1
    print('Our final balance is', round(balance, 2))
    return balance

def new_balance(balance, rate, years):
    ''' A function that evaluates the new
balance after the input years at a give rate '''
    print('Balance at the beginning:', balance)
    y = 0
    while y < years:
        interest = balance * rate
        balance = balance + interest
        print('Balance after', y, 'year:', round(balance, 2))
        y = y+1
    print('Our final balance is', round(balance, 2))
    return balance


def new_ebike(balance, rate, ebike):
    ''' A function that evaluates the number
of years we have to wait in order to
buy an ebike that costs ebike yuan '''
    y = 0
    while balance < ebike:
        interest = balance * rate
        balance = interest + balance
        y = y + 1
    print('We can buy ebike', y, 'years later.')
    return y

