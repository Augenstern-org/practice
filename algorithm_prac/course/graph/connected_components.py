def count_connected_components(graph):
    """
    TODO X:
    Count how many connected components are in an undirected graph.

    Parameters:
    - graph: adjacency list

    Returns:
    - number of connected components

    Hint:
    - Iterate over all nodes.
    - Each time you find an unvisited node, run BFS (or DFS).
    - All nodes reached belong to the same component.

    Question:
    Why do we not run BFS from every node?
    """
    # TODO: implement this function
    pass


def test_connected_components_complex():
    print("\n=== CONNECTED COMPONENTS (COMPLEX) ===")

    # Components:
    # {0,1,2}, {3}, {4,5}, {6,7,8}
    graph = [
        [1, 2],     # 0
        [0],        # 1
        [0],        # 2
        [],         # 3
        [5],        # 4
        [4],        # 5
        [7],        # 6
        [6, 8],     # 7
        [7]         # 8
    ]

    print("Number of connected components:")
    print(count_connected_components(graph))

    print("\nExpected:")
    print("4")
