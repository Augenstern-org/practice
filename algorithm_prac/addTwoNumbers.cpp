// Created by Neuroil on 2026/03/30

/* * 题目：两数相加 (Add Two Numbers)
 * * [题目要求]
 * 给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * * [示例说明]
 * 示例 1：l1 = [2,4,3], l2 = [5,6,4] -> 输出 [7,0,8] (342 + 465 = 807)
 * 示例 2：l1 = [0], l2 = [0]          -> 输出 [0]
 * 示例 3：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] -> 输出 [8,9,9,9,0,0,0,1]
 * * [提示与进阶]
 * 1. 每个链表中的节点数在范围 [1, 100] 内。
 * 2. 0 <= Node.val <= 9。
 * 3. 题目保证列表表示的数字不含前导零。
 */

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

class Solution {
  public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* this_node = new ListNode();
        ListNode* head = this_node;
        while (cur1 != nullptr || cur2 != nullptr) {
            ListNode* next_node = new ListNode();
            int sum = 0;
            if (cur1 == nullptr) {
                sum = cur2->val + carry;
            } else if (cur2 == nullptr) {
                sum = cur1->val + carry;
            } else {
                sum = cur1->val + cur2->val + carry;
            }
            carry = sum / 10;
            this_node->val = sum % 10;

            if (carry != 0 || cur1 != nullptr || cur2 != nullptr) {
                this_node->next = next_node;
                this_node = next_node;
            }
            if (cur1 != nullptr) cur1 = cur1->next;
            if (cur2 != nullptr) cur2 = cur2->next;
        }
        this_node->val = carry;
        return head;
    }
};

class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0); // 哨兵节点
        ListNode* cur = dummy;
        int carry = 0; // 进位初始化为 0

        // 只要 l1, l2 没走完，或者最后还有一个进位 carry 需要处理
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry; // 先把上一轮的进位加进来
            
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10; // 计算新的进位（比如 13 / 10 = 1）
            
            // 创建当前位的结果节点并连接
            cur->next = new ListNode(sum % 10); // 比如 13 % 10 = 3
            cur = cur->next;
        }

        ListNode* result = dummy->next;
        delete dummy; // 释放哨兵
        return result;
    }
};

class Solution3 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 创建一个虚拟头节点，方便操作
        ListNode* dummyHead = new ListNode(-1);
        ListNode* current = dummyHead;
        int carry = 0;

        // 循环条件：只要有一个链表没走完，或者还有进位，就需要继续
        while (l1 != nullptr || l2 != nullptr || carry > 0) {
            int sum = carry; // 初始化当前位的和为进位值

            // 如果 l1 还有节点，则加上它的值，并移动指针
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }

            // 如果 l2 还有节点，则加上它的值，并移动指针
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            // 计算新节点的值和新的进位
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next; // 移动到下一个节点
        }

        // 获取真正的头节点，并释放虚拟头节点
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};

int main() {
    Solution2 sol;
    string templateName = "Add Two Numbers";

    // 测试名向量
    vector<string> sn = {"Standard addition without carry-out at the end",
                         "Both numbers are zero", "Lists of different lengths",
                         "Addition resulting in an extra carry at the end",
                         "Long lists with multiple carries"};

    // 测试数据
    vector<vector<int>> input1 = {{2, 4, 3}, {0}, {9, 9}, {5}, {9, 9, 9}};
    vector<vector<int>> input2 = {{5, 6, 4}, {0}, {1}, {5}, {1}};
    vector<vector<int>> expected = {
        {7, 0, 8}, {0}, {0, 0, 1}, {0, 1}, {0, 0, 0, 1}};

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        ListNode* l1 = createLinkedList(input1[i]);
        ListNode* l2 = createLinkedList(input2[i]);

        // 执行待测函数
        ListNode* resultNode = sol.addTwoNumbers(l1, l2);
        vector<int> resultVec = listToVector(resultNode);

        // 输出对比
        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    L1: [";
        for (int n : input1[i])
            cout << n << (n == input1[i].back() ? "" : ",");
        cout << "], L2: [";
        for (int n : input2[i])
            cout << n << (n == input2[i].back() ? "" : ",");
        cout << "]" << endl;

        cout << "  Result:   [";
        for (int j = 0; j < resultVec.size(); ++j)
            cout << resultVec[j] << (j == resultVec.size() - 1 ? "" : ",");
        cout << "]" << endl;

        cout << "  Expected: [";
        for (int j = 0; j < expected[i].size(); ++j)
            cout << expected[i][j] << (j == expected[i].size() - 1 ? "" : ",");
        cout << "]" << endl;

        bool isPass = (resultVec == expected[i]);
        cout << "  Status:   "
             << (isPass ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
             << endl;
        cout << "------------------------------------" << endl;

        freeList(l1);
        freeList(l2);
        freeList(resultNode);
    }

    return 0;
}