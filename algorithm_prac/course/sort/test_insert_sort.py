import time
import random

def insertSort(target):
    for i in range(1, len(target)):
        j = i - 1
        key = target[i]
        while j >= 0 and target[j] > key:
            target[j+1] = target[j]
            j -= 1
        target[j+1] = key

# 动态输入长度
n = int(input("请输入要排序的数据个数: "))
a = [random.randint(0, 10**6) for _ in range(n)]

# print("排序前:", a[:min(10, len(a))], "..." if len(a) > 10 else "")
print("开始排序...")
start_time = time.perf_counter()
insertSort(a)
end_time = time.perf_counter()
# print("排序后:", a[:min(10, len(a))], "..." if len(a) > 10 else "")
print(f"执行时间: {end_time - start_time:.6f} 秒")
