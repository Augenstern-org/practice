from math import pi
one = 1

def radius(volume):
    return (3*volume/4/pi)**(1/3)

def surface(radius):
    return 4*pi*radius**2


def volume(radius):
    return 4/3*pi*radius**3

def print_volume(radius):
    print(4/3*pi*radius**3)
