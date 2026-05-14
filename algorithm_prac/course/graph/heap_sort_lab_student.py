"""
Lab: Heap Sort
===============================

Goal:
Implement heap sort with most of the structure already given.

You will complete the helper functions and the main heap sort logic.
"""

import time
import random


# ============================================================
# PART 1 — Helper functions
# ============================================================

def left_child(i):
    """
    Return the index of the left child of node i.
    """
    return 2 * i + 1          # 已补全


def right_child(i):
    """
    Return the index of the right child of node i.
    """
    return 2 * i + 2          # 已补全


def swap(A, i, j):
    """
    Swap the elements at positions i and j.
    """
    A[i], A[j] = A[j], A[i]   # 已补全


# ============================================================
# PART 2 — Heapify down
# ============================================================

def heapify_down(A, i, heap_size):
    """
    Restore the max-heap property starting from index i.

    Only the part A[0:heap_size] belongs to the heap.
    """

    while True:
        left = left_child(i)
        right = right_child(i)

        largest = i

        # 已补全：如果左孩子存在且大于当前最大，则更新
        if left < heap_size and A[left] > A[largest]:
            largest = left

        # 已补全：如果右孩子存在且大于当前最大，则更新
        if right < heap_size and A[right] > A[largest]:
            largest = right

        if largest == i:
            break

        swap(A, i, largest)
        i = largest


# ============================================================
# PART 3 — Build a max-heap
# ============================================================

def build_max_heap(A):
    """
    Transform A into a max-heap.
    """

    n = len(A)
    last_internal_node = (n // 2) - 1

    # 已补全：从最后一个内部节点向下到根，依次 heapify_down
    for i in range(last_internal_node, -1, -1):
        heapify_down(A, i, n)


# ============================================================
# PART 4 — Heap sort
# ============================================================

def heap_sort(numbers):
    """
    Return a sorted copy of numbers using heap sort.
    """

    A = numbers.copy()
    n = len(A)

    build_max_heap(A)          # 已补全：建堆

    heap_size = n

    for end in range(n - 1, 0, -1):

        # 已补全：将最大值（根）与位置 end 交换
        swap(A, 0, end)

        # 已补全：堆大小减1
        heap_size -= 1

        # 已补全：从根开始恢复堆性质
        heapify_down(A, 0, heap_size)

    return A


# ============================================================
# PART 5 — Insertion sort for comparison
# ============================================================

def insertion_sort(numbers):
    """
    Sort numbers using insertion sort.
    """

    for j in range(1, len(numbers)):
        key = numbers[j]
        i = j - 1

        while i >= 0 and numbers[i] > key:
            numbers[i + 1] = numbers[i]
            i -= 1

        numbers[i + 1] = key

    return numbers


def measure_time(function, data):
    """
    Measure the execution time of a sorting function.
    """

    start = time.time()
    function(data.copy())
    end = time.time()

    return end - start


# ============================================================
# PART 6 — Questions
# ============================================================

"""
Answer these questions:

1. Why do we build a max-heap and not a min-heap?

2. What is the meaning of heap_size?

3. During heap sort, which part of the array is the heap?
   Which part is already sorted?

4. Why do we call heapify_down after each swap?

5. What is the time complexity of heap sort?

6. Compare heap sort and insertion sort on large random arrays.
   Which one becomes faster as n grows?

7. Why does insertion sort become slow on large random arrays?

8. Try the experiment with an already sorted list:
   data = list(range(n))

   What changes?
"""


# ============================================================
# PART 7 — Tests and comparison
# ============================================================

if __name__ == "__main__":
    tests = [
        [4, 10, 3, 5, 1],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [7],
        [],
        [4, 1, 4, 2, 4],
        [10, -1, 3, 0, 2],
    ]

    print("TESTS")
    print("=" * 40)

    for data in tests:
        result = heap_sort(data)
        expected = sorted(data)

        print("Input:   ", data)
        print("Output:  ", result)
        print("Expected:", expected)
        print("Correct? ", result == expected)
        print("-" * 40)

    print()
    print("COMPARISON: Heap Sort vs Insertion Sort")
    print("=" * 50)

    sizes = [100, 1000, 3000, 5000]

    for n in sizes:
        data = [random.randint(0, 100000) for _ in range(n)]

        heap_time = measure_time(heap_sort, data)
        insertion_time = measure_time(insertion_sort, data)

        print("n =", n)
        print("Heap sort time:     ", heap_time)
        print("Insertion sort time:", insertion_time)
        print("-" * 40)