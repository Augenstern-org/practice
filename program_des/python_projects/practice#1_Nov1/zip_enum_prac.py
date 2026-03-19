# 使用zip处理多个列表
def combine_lists(names, ages, scores):
    """将多个列表合并为字典列表"""
    z1 = zip(names, ages)
    r_dict = dict(zip(z1, scores))
    return r_dict
    pass

# 使用enumerate获取索引和值
def find_indices(lst, target):
    """找出列表中所有目标元素的索引"""
    pass

