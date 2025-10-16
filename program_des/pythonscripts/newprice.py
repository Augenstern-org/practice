def newprice(price):
    discount = 20
    price = price * (1-discount/100)
    return round(price, 1)

def newprice_disc(price, discount):
    price = price * (1-discount/100)
    return round(price, 1)

print(newprice(12))
print(newprice(15))
