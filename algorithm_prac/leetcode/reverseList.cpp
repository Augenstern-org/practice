// Created by Neuroil on 2026/03/30

/* * 题目：反转链表 (Reverse Linked List)
 * * [题目要求]
 * 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 * * [示例说明]
 * 示例 1：输入 head = [1,2,3,4,5] -> 输出 [5,4,3,2,1]
 * 示例 2：输入 head = [1,2]       -> 输出 [2,1]
 * 示例 3：输入 head = []          -> 输出 []
 * * [提示与进阶]
 * 1. 链表中节点的数目范围是 [0, 5000]。
 * 2. -5000 <= Node.val <= 5000。
 * 3. 进阶：你能否分别用迭代和递归两种方法解决这道题？
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// --- 工具函数：根据 vector 创建链表 ---
ListNode* createLinkedList(const vector<int>& nums) {
    if (nums.empty()) return nullptr;
    ListNode* head = new ListNode(nums[0]);
    ListNode* cur = head;
    for (size_t i = 1; i < nums.size(); ++i) {
        cur->next = new ListNode(nums[i]);
        cur = cur->next;
    }
    return head;
}

// --- 工具函数：将链表转回 vector ---
vector<int> listToVector(ListNode* head) {
    vector<int> res;
    while (head) {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

// --- 工具函数：释放链表内存 ---
void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

class Solution_0 {
  public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummy = new ListNode(head->val, head->next);
        ListNode* pre = dummy;
        if (head->next->next == nullptr) {
            ListNode* h = pre->next;
            h->next = pre;
            pre->next = nullptr;
            delete dummy;
            return h;
        } else {
            ListNode* cur = pre->next;
            ListNode* nex = cur->next;
            pre->next = nullptr;
            while (nex != nullptr) {
                nex = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nex;
            }
            delete dummy;
            return cur;
        }
    }
};

class Solution {
  public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr; // 最终它会变成新的头
        ListNode* curr = head;    // 正在处理的节点

        while (curr != nullptr) {
            // 1. 赶紧把“next”存起来，不然等下箭头一调头，后面就找不到了
            ListNode* nextTemp = curr->next;

            // 2. 核心动作：调转箭头，指向前一个人
            curr->next = prev;

            // 3. 所有人向后移一步，准备处理下一个
            prev = curr;     // 前任变成当前
            curr = nextTemp; // 当前变成刚才存好的那个“next”
        }

        // 当 curr 走出链表（变 null）时，prev 正好停在原链表的最后一个节点
        return prev;
    }
};

class Solution2 {
  public:
    ListNode* reverseList(ListNode* head) {
        // 递归终止条件：如果是空或者只有一个节点，直接返回
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // 这里的 newHead 永远指向原链表的最后一个节点（也就是翻转后的新头）
        ListNode* newHead = reverseList(head->next);

        // 核心：让“我的下一个”指向“我”
        head->next->next = head;
        // 把“我”原来的指向断开，防止形成环
        head->next = nullptr;

        return newHead;
    }
};

int main() {
    Solution sol;
    string templateName = "Reverse Linked List";

    // 测试名向量
    vector<string> sn = {"Normal list with multiple nodes",
                         "List with two nodes", "Single node list",
                         "Empty list", "Longer list with sequential values"};

    // 测试数据
    vector<vector<int>> inputs = {
        {1, 2, 3, 4, 5}, {1, 2}, {1}, {}, {10, 20, 30, 40, 50, 60}};

    // 生成预期结果（将输入翻转）
    vector<vector<int>> expecteds = inputs;
    for (auto& v : expecteds) {
        reverse(v.begin(), v.end());
    }

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        ListNode* head = createLinkedList(inputs[i]);

        // 执行待测函数
        ListNode* resultNode = sol.reverseList(head);
        vector<int> resultVec = listToVector(resultNode);

        // 输出对比
        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;

        cout << "  Input:    [";
        for (int j = 0; j < inputs[i].size(); ++j)
            cout << inputs[i][j] << (j == inputs[i].size() - 1 ? "" : ",");
        cout << "]" << endl;

        cout << "  Result:   [";
        for (int j = 0; j < resultVec.size(); ++j)
            cout << resultVec[j] << (j == resultVec.size() - 1 ? "" : ",");
        cout << "]" << endl;

        cout << "  Expected: [";
        for (int j = 0; j < expecteds[i].size(); ++j)
            cout << expecteds[i][j]
                 << (j == expecteds[i].size() - 1 ? "" : ",");
        cout << "]" << endl;

        bool isPass = (resultVec == expecteds[i]);
        cout << "  Status:   "
             << (isPass ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
             << endl;
        cout << "------------------------------------" << endl;

        // 清理结果链表内存
        freeList(resultNode);
    }

    return 0;
}