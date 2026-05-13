def dfs(graph, start):
    """
    TODO 4:
    Implement Depth-First Search.

    DFS explores one path as deeply as possible before going back.

    Parameters:
    - graph: adjacency list
    - start: starting vertex

    Returns:
    - a list containing the order in which vertices are visited

    Hint:
    - Use a set called visited.
    - Use a stack.
    - In Python, a list can be used as a stack.
    - Use stack.append(x) to push.
    - Use stack.pop() to remove the last inserted element.

    Question:
    What is the main difference between BFS and DFS?
    """
    # TODO: implement this function
    pass


def test_dfs():
    """
    Test DFS.
    """
    print("\n=== DFS ===")

    graph = [
        [1, 2, 3],
        [0, 4],
        [0],
        [0],
        [1]
    ]

    print("DFS from node 0:")
    print(dfs(graph, 0))

    print("\nOne possible expected output:")
    print("[0, 3, 2, 1, 4]")
    print("Note: DFS order can change depending on the order in which neighbors are pushed.")
