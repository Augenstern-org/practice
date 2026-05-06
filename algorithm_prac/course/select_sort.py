a = [7,5,3,1,54,5,8,4,2,88,7,91,8]
def select_sort(target):
    for i in range(len(target)-1):
        ith = i
        for j in range(i+1, len(target)):
            if target[j] < target[ith]:
                ith = j
        target[i],target[ith] = target[ith],target[i]
        # print("--->",target)
            
print(a)
print("After Sort:")
select_sort(a)
print(a)
