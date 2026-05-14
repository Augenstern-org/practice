#include <iostream>

struct Node {
    int val;
    Node* prev;
    Node* next;

    Node() : val(0), prev(nullptr), next(nullptr) {}
    Node(int v) : val(v), prev(nullptr), next(nullptr) {}
    Node(int v, Node* p, Node* n) : val(v), prev(p), next(n) {}
};

struct Array {
    int len;
    int* data;

    Array(int start, int end) : len(end - start) {
        data = new int[len];
        for (int i = start; i < end; ++i) data[i - start] = i;
    }
    // Array(const Array&) = delete;

    // void operator=(const Array&) = delete;

    Array(const Array& target):len(target.len){
        data = new int[len];
        for(int i = 0; i != len; ++i) this->data[i] = target.data[i];
    }
    const int operator[](int index) const { return data[index]; }

    ~Array() { delete[] data; }
};

// Node* createNodeList(Array& num) {
//     Node* head = new Node(num[0]);
//     Node* prevNode = head;
//     for (int i = 1; i != num.len; ++i) {
//         Node* currNode = new Node(num[i]);
//         currNode->prev = prevNode;
//         prevNode->next = currNode;
//         prevNode = currNode;
//     }
//     return head;
// }

Node* createNodeList(Array num) {
    Node* head = new Node(num[0]);
    Node* prevNode = head;
    for (int i = 1; i != num.len; ++i) {
        Node* currNode = new Node(num[i]);
        currNode->prev = prevNode;
        prevNode->next = currNode;
        prevNode = currNode;
    }
    return head;
}

void releaseNodeList(Node* head) {
    Node* next = head->next;
    while (head) {
        delete head;
        head = next;
        if (next) next = next->next;
    }
}

void print(const Array& target) {
    std::cout << "[ ";
    for (int i = 0; i != target.len - 1; ++i) {
        std::cout << target[i] << ", ";
    }
    std::cout << target[target.len - 1] << " ]" << std::endl;
}

void print(const Node* head) {
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    Array test(0, 10);
    print(test);
    Node* head = createNodeList(test);
    print(head);
    releaseNodeList(head);
}
