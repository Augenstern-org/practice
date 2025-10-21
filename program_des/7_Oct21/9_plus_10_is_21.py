import random

def write_random_num(filename, times):
    with open(filename, 'a') as file:
        for t in range(1, times+1):
            file.write(str(t))
            file.write(": ")
            file.write(str(random.random()))
            file.write("\n")

f = "test_output.txt"

#write_random_num(f, 10)


def sigh_num_to_word(filename):
    n = 1
    input = open(filename, 'r')
    output = open("output.txt", 'w')
    i = input.readline()
    while i:
        o = str(n) + " " + i
        n += 1
        i = input.readline()
        output.writelines(o)

sigh_num_to_word("test_input.txt")


