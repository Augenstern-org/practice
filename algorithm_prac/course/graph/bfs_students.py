def bfs(graph, start):
    """
    TODO 3:
    实现广度优先搜索。

    BFS 逐层访问顶点：
    - 首先访问起始顶点
    - 然后访问它的所有邻居
    - 然后访问那些邻居的邻居
    - 依此类推

    参数：
    - graph: 邻接表
    - start: 起始顶点

    返回：
    - 一个列表，包含顶点被访问的顺序

    提示：
    - 使用一个名为 visited 的集合。
    - 使用一个队列。
    - 在 Python 中，从 collections 导入 deque。
    - 使用 queue.append(x) 来入队。
    - 使用 queue.popleft() 从队首取出元素。

    问题：
    为什么我们需要 visited 集合？
    """
    # TODO: 实现此函数
    pass


def test_bfs():
    """
    测试 BFS。
    """
    print("\n=== BFS ===")

    graph = [
        [1, 2, 3],
        [0, 4],
        [0],
        [0],
        [1]
    ]

    print("从节点 0 开始 BFS：")
    print(bfs(graph, 0))

    print("\n预期输出：")
    print("[0, 1, 2, 3, 4]")