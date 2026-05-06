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

    Array(int start, int end) : len(end - start + 1) {
        data = new int[len];
        for (int i = start; i <= end; ++i) data[i - start] = i;
    }

    void operator=(Array) = delete;
    int operator[](int index) { return data[index]; }

    ~Array() { delete[] data; }
};

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

void releaseNodeList(Node* head){
    Node* curr = head;
    Node* next = head->next;
    while(curr){
        delete curr;
        curr = next;
        next = curr->next;
    }
}
