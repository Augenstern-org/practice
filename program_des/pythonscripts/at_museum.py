def total_amount(people, ticket):
    ''' A function that returns the
total amount to pay when going to the
museum. You get a discount for 10 or
more people'''
    if people<10:
        print('No discount for you')
        return people*ticket
    else:
        if people<50:
            print('There is a small discount!!')
            return people*ticket*0.8
        else:
            print('There is a big discount!!')
            return people*ticket*0.6


def total_amount_elif(people, ticket):
    if people<10:
        print('No discount for you')
        return people*ticket
    elif people<50:
        print('There is a small discount!!')
        return people*ticket*0.8
    else:
        print('There is a big discount!!')
        return people*ticket*0.6

