# 找出列表中绝对值最大的元素
def max_abs_value(numbers):
    pass

# 找出字典中值最大的键值对
def max_value_item(dictionary):
    pass

# 找出学生成绩中的最高分及对应的学生
students = [
    {'name': 'Alice', 'score': 85},
    {'name': 'Bob', 'score': 92},
    {'name': 'Charlie', 'score': 78}
]

def find_top_student(students):
    target = max(students, key= lambda x: students[x])
    return target
    pass


# 按多个条件排序
products = [
    {'name': 'Laptop', 'price': 999, 'rating': 4.5},
    {'name': 'Phone', 'price': 699, 'rating': 4.8},
    {'name': 'Tablet', 'price': 299, 'rating': 4.2}
]

def sort_products(products):
    """先按评分降序，再按价格升序排序"""
    pass

# 自定义排序规则
def custom_sort(strings):
    """按字符串长度排序，长度相同则按字母顺序"""
    pass

