"""
Lab: Basic Data Structures in Python 
Arrays, linked lists, stacks, queues

Goal:
Understand how the choice of data structure changes the cost of operations.

We use:
- Python list as an array-like structure
- A simple linked list implemented manually
- Stack and queue abstractions
- collections.deque for an efficient queue implementation

Instructions:
1. Read each part carefully.
2. Complete the TODO sections.
3. Run the file and observe the output.
4. Answer the questions in the comments.
"""

import time
from collections import deque


# ============================================================
# PART 1 — Python list as an array-like structure
# ============================================================

def test_array_operations(n):
    """
    This function is already implemented.

    Run it and observe:
    - access to the middle element
    - insertion at the front
    - insertion at the back

    Questions:
    1. Which operation is fastest?
    2. Which operation becomes slower as n grows?
    3. Why is insert(0, x) slower than append(x)?
    """
    A = list(range(n))

    print("\n=== ARRAY OPERATIONS ===")
    print("n =", n)

    start = time.time()
    _ = A[n // 2]
    end = time.time()
    print("Array access A[n//2]:", end - start)

    start = time.time()
    A.insert(0, -1)
    end = time.time()
    print("Array insert at front:", end - start)

    start = time.time()
    A.append(-2)
    end = time.time()
    print("Array insert at back:", end - start)


# ============================================================
# PART 2 — Linked list
# ============================================================

class Node:
    """
    A node of a singly linked list.

    Each node stores:
    - value: the data
    - next: a reference to the next node
    """

    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedList:
    """A simple singly linked list."""

    def __init__(self):
        self.first = None

    def insert_front(self, x):
        """
        Insert x at the beginning of the linked list.

        This method is already implemented.
        """
        new_node = Node(x)
        new_node.next = self.first
        self.first = new_node

    def access(self, i):
        """
        TODO 1:
        Return the value of the i-th element of the linked list.

        If i is out of bounds, return None.

        Hint:
        - Start from self.first
        - Move forward using current.next
        - Count how many nodes you have visited

        Example:
        If the list is 10 -> 20 -> 30 -> None
        access(0) returns 10
        access(1) returns 20
        access(2) returns 30
        access(5) returns None
        """
        # TODO: implement this method
        cnt = 0
        curr = self.first
        while curr != None and cnt < i:
            temp = curr.next
            cnt += 1
            curr = temp
        if curr == None:
            return None
        return curr.value
        pass

    def print_list(self, max_nodes=20):
        """
        TODO 2:
        Print the linked list.

        Example output:
        1 -> 2 -> 3 -> None

        max_nodes avoids printing huge lists.
        """
        # TODO: implement this method
        curr = self.first
        while curr != None:
            print(curr.value,"-> ",end="")
            temp = curr.next
            curr = temp
        print("None")
        pass

    def size(self):
        """
        TODO 3:
        Return the number of nodes in the linked list.

        Question:
        What is the running time of this method?
        """
        # TODO: implement this method
        cnt = 0
        curr = self.first
        while curr != None:
            temp = curr.next
            curr = temp
            cnt += 1
        return cnt
        pass

    def insert_at(self, i, x):
        """
        TODO 4:
        Insert x at position i.

        If i == 0, insert at the front.
        If i is larger than the list size, do nothing.

        Example:
        list: 1 -> 2 -> 3 -> None
        insert_at(1, 99)
        result: 1 -> 99 -> 2 -> 3 -> None

        Question:
        Why is this not O(1) in general?
        """
        if i == 0:
            self.insert_front(x)
            return

        prev = None
        curr = self.first
        cnt = 0

        while curr is not None and cnt < i:
            prev = curr
            curr = curr.next
            cnt += 1

        if cnt != i or prev is None:
            return

        new_node = Node(x)
        prev.next = new_node
        new_node.next = curr


def build_linked_list(n):
    """
    Build a linked list containing 0, 1, 2, ..., n-1.

    This function is already implemented.
    """
    L = LinkedList()

    for x in range(n - 1, -1, -1):
        L.insert_front(x)

    return L


def test_linked_list_operations(n):
    """
    Test access and insertion at front on a linked list.

    Questions:
    1. Why is linked list access slower than array access?
    2. Why is insert_front fast?
    """
    L = build_linked_list(n)

    print("\n=== LINKED LIST OPERATIONS ===")
    print("n =", n)

    start = time.time()
    _ = L.access(n // 2)
    end = time.time()
    print("Linked list access middle:", end - start)

    start = time.time()
    L.insert_front(-1)
    end = time.time()
    print("Linked list insert at front:", end - start)


def demo_small_linked_list():
    """
    Small example to test your linked list implementation.
    """
    print("\n=== SMALL LINKED LIST DEMO ===")

    L = LinkedList()
    L.insert_front(3)
    L.insert_front(2)
    L.insert_front(1)

    print("Initial list:")
    L.print_list()

    print("Access index 0:", L.access(0))
    print("Access index 1:", L.access(1))
    print("Access index 2:", L.access(2))
    print("Access index 10:", L.access(10))

    L.insert_at(1, 99)
    print("After insert_at(1, 99):")
    L.print_list()

    print("Size:", L.size())


# ============================================================
# PART 3 — Stack
# ============================================================

class Stack:
    """
    TODO 5:
    Implement a stack using a Python list.

    Stack operations:
    - push(x): add x on top
    - pop(): remove and return top element
    - top(): return top element without removing it

    A stack follows LIFO:
    Last In, First Out
    """

    def __init__(self):
        self.data = []

    def push(self, x):
        # TODO: implement push
        self.data.append(x)
        pass

    def pop(self):
        # TODO: implement pop
        # If the stack is empty, return None
        size = len(self.data)
        if size == 0:
            return None
        res = self.data[size-1]
        self.data.pop(size-1)
        return res
        pass

    def top(self):
        # TODO: implement top
        # If the stack is empty, return None
        size = len(self.data)
        if size == 0:
            return None
        return self.data[size-1]
        pass

    def is_empty(self):
        # TODO: return True if the stack is empty
        if len(self.data) == 0:
            return True
        return False
        pass


def test_stack():
    """
    Test your stack implementation.

    Question:
    After pushing 10, 20, 30, why does pop() return 30 first?
    """
    print("\n=== STACK ===")

    S = Stack()

    S.push(10)
    S.push(20)
    S.push(30)

    print("After push(10), push(20), push(30)")
    print("Stack top:", S.top())
    print("Stack pop:", S.pop())
    print("Stack pop:", S.pop())
    print("Stack top:", S.top())


# ============================================================
# PART 4 — Queue using Python list
# ============================================================

class Queue:
    """
    TODO 6:
    Implement a queue using a Python list.

    Queue operations:
    - enqueue(x): add x at the back
    - dequeue(): remove and return the front element

    A queue follows FIFO:
    First In, First Out
    """

    def __init__(self):
        self.data = []

    def enqueue(self, x):
        # TODO: implement enqueue
        self.data.append(x)
        pass

    def dequeue(self):
        # TODO: implement dequeue
        # If the queue is empty, return None
        if self.is_empty():
            return None
        res = self.data[0]
        self.data.pop(0)
        return res
        pass

    def is_empty(self):
        # TODO: return True if the queue is empty
        if len(self.data) == 0:
            return True
        return False 
        pass


def test_queue():
    """
    Test your queue implementation.

    Question:
    After enqueue(10), enqueue(20), enqueue(30), why does dequeue() return 10 first?
    """
    print("\n=== QUEUE ===")

    Q = Queue()

    Q.enqueue(10)
    Q.enqueue(20)
    Q.enqueue(30)

    print("After enqueue(10), enqueue(20), enqueue(30)")
    print("Queue dequeue:", Q.dequeue())
    print("Queue dequeue:", Q.dequeue())


def test_queue_performance(n):
    """
    Measure the cost of repeatedly dequeuing from a list-based queue.

    Question:
    Why is this slow?
    Hint:
    Think about what happens when we call pop(0).
    """
    Q = Queue()

    for i in range(n):
        Q.enqueue(i)

    start = time.time()
    for _ in range(n):
        Q.dequeue()
    end = time.time()

    print("\n=== LIST-BASED QUEUE PERFORMANCE ===")
    print("n =", n)
    print("Total dequeue time:", end - start)


# ============================================================
# PART 5 — Efficient queue using collections.deque
# ============================================================

class FastQueue:
    """
    This queue uses collections.deque.

    TODO 7:
    Complete enqueue and dequeue using:
    - append
    - popleft
    """

    def __init__(self):
        self.data = deque()

    def enqueue(self, x):
        # TODO: implement enqueue
        self.data.append(x)
        pass

    def dequeue(self):
        # TODO: implement dequeue
        # If the queue is empty, return None
        if self.is_empty():
            return None
        return self.data.popleft()
        pass

    def is_empty(self):
        # TODO: return True if the queue is empty
        if len(self.data) == 0:
            return True
        return False 
        pass


def test_fast_queue_performance(n):
    """
    Compare this with the list-based queue.

    Question:
    Why is this faster?
    """
    Q = FastQueue()

    for i in range(n):
        Q.enqueue(i)

    start = time.time()
    for _ in range(n):
        Q.dequeue()
    end = time.time()

    print("\n=== DEQUE-BASED QUEUE PERFORMANCE ===")
    print("n =", n)
    print("Total dequeue time:", end - start)


# ============================================================
# MAIN
# ============================================================

if __name__ == "__main__":
    # You can increase or decrease n depending on the speed of the machine.
    n = 100000

    test_array_operations(n)

    # Uncomment this after implementing LinkedList methods.
    demo_small_linked_list()
    test_linked_list_operations(n)

    # Uncomment this after implementing Stack.
    test_stack()

    # Uncomment this after implementing Queue.
    test_queue()

    # Use a smaller n if computers are slow.
    queue_n = 50000

    # Uncomment after implementing Queue.
    test_queue_performance(queue_n)

    # Uncomment after implementing FastQueue.
    test_fast_queue_performance(queue_n)

    print("\n=== FINAL QUESTIONS ===")
    print("1. Why is array access faster than linked list access?")
    print("2. Why is linked list insert_front faster than array insert(0, x)?")
    print("3. Why is list-based dequeue slow?")
    print("4. Why do different data structures exist?")
