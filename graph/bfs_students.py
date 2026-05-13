def bfs(graph, start):
    """
    TODO 3:
    Implement Breadth-First Search.

    BFS visits vertices level by level:
    - first the starting vertex
    - then all its neighbors
    - then the neighbors of those neighbors
    - and so on

    Parameters:
    - graph: adjacency list
    - start: starting vertex

    Returns:
    - a list containing the order in which vertices are visited

    Hint:
    - Use a set called visited.
    - Use a queue.
    - In Python, use deque from collections.
    - Use queue.append(x) to insert.
    - Use queue.popleft() to remove from the front.

    Question:
    Why do we need the visited set?
    """
    # TODO: implement this function
    pass


def test_bfs():
    """
    Test BFS.
    """
    print("\n=== BFS ===")

    graph = [
        [1, 2, 3],
        [0, 4],
        [0],
        [0],
        [1]
    ]

    print("BFS from node 0:")
    print(bfs(graph, 0))

    print("\nExpected:")
    print("[0, 1, 2, 3, 4]")

