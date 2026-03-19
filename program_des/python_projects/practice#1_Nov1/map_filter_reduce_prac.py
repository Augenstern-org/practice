from functools import reduce

# 使用map转换数据
def convert_temperatures(celsius_list):
    """将摄氏度列表转换为华氏度"""
    rlist = list(map(lambda x: round(x*1.8 + 32, ndigits=2), celsius_list))
    return rlist
    pass

# 使用filter筛选数据
def filter_adults(people):
    """筛选出成年人（年龄>=18）"""
    return list(filter(lambda x: x >= 18, people))
    pass

# 使用reduce计算
def calculate_product(numbers):
    """计算列表中所有数字的乘积"""
    return reduce(lambda x, y: x * y, numbers)
    pass

# 组合使用
def process_data(numbers):
    """先过滤偶数，再平方，最后求和"""
    non_o_lst = filter(lambda x: x % 2 == 0, numbers)
    d_lst = map(lambda x: x ** 2, non_o_lst)
    return reduce(lambda x, y: x + y, d_lst)
    pass

# 测试convert_temperatures
print(convert_temperatures([0, 20, 37, 100]))  # [32.0, 68.0, 98.6, 212.0]

# 测试filter_adults
print(filter_adults([17, 18, 20, 15, 25]))  # [18, 20, 25]

# 测试calculate_product
print(calculate_product([1, 2, 3, 4]))  # 24（修正后）

# 测试process_data
print(process_data([1, 2, 3, 4, 5, 6]))  # 56（2² + 4² + 6² = 4 + 16 + 36 = 56）




