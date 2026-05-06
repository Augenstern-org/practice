a = [1,4,2,5,8,3,1,4,2,23]

def insertSort(target):
    for i in range(1, len(target)):
        j = i - 1
        key = target[i]
        while j >= 0 and target[j] > key:
            target[j+1] = target[j]
            j -= 1
        target[j+1] = key
        # print("-->   ", a)

print(a)
print("insertSort(a):")
insertSort(a)
print(a)
