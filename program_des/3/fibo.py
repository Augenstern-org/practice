def fibo(ranks):
    fir = 1
    sec = 1
    if ranks == 1 or ranks == 2:
        return 1
    else:
        for i in range(ranks-2):
            temp = fir + sec
            fir = sec
            sec = temp
        return sec


a = int(input("type: "))
print(fibo(a))
