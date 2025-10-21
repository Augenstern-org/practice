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

#sigh_num_to_word("test_input.txt")

def split_and_sum(filename):
    int_sum = 0
    float_sum = 0.0
    with open(filename, 'r') as file:
        for line in file:
            list = line.split(" ")
            for index in list:
                try:
                    int_sum += int(index)
                except ValueError:
                    float_sum += float(index)
    print(int_sum, float_sum)

sum = "int_float.txt"
#split_and_sum(sum)


