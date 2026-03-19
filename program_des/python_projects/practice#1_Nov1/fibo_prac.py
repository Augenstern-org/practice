# 使用递归实现
def fibonacci_recursive(n):
    """计算第n个斐波那契数（递归版）"""
    if n == 1 or n == 2:
        return 1
    return fibonacci_recursive(n-1)+fibonacci_recursive(n-2)
    pass

# 使用迭代实现
def fibonacci_iterative(n):
    """计算第n个斐波那契数（迭代版）"""
    if n == 1 or n == 2:
        return 1
    fir = 1
    sec = 1
    temp = 0
    for i in range(1, n-1):
        temp = fir + sec
        fir = sec
        sec = temp
    return sec
    pass

# 使用生成器实现
def fibonacci_generator(n):
    """生成前n个斐波那契数（生成器版）"""
    pass

print(fibonacci_recursive(3))
print(fibonacci_iterative(4))
print(fibonacci_iterative(5))
print(fibonacci_iterative(6))


