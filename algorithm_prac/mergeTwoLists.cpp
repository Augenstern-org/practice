// Created by Neuroil on 2026/03/30

/* * 题目：合并两个有序链表 (Merge Two Sorted Lists)
 * * [题目要求]
 * 将两个升序链表合并为一个新的升序链表并返回。
 * 新链表是通过拼接给定的两个链表的所有节点组成的。
 * * [示例说明]
 * 示例 1：输入 l1 = [1,2,4], l2 = [1,3,4] -> 输出 [1,1,2,3,4,4]
 * 示例 2：输入 l1 = [], l2 = []          -> 输出 []
 * 示例 3：输入 l1 = [], l2 = [0]         -> 输出 [0]
 * * [提示与进阶]
 * 1. 两个链表的节点数目范围是 [0, 50]。
 * 2. -100 <= Node.val <= 100。
 * 3. l1 和 l2 均按非递减顺序排列。
 */

#include <iomanip>
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

// --- 工具函数：将链表转回 vector 方便对比 ---
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* temp;
        ListNode* res;
        if (list1->val < list2->val) {
            res->next = list1->next;
            res->val = list1->val;
            temp->next = list1;
        } else {
            res->next = list2->next;
            res->val = list2->val;
            temp->next = list2;
        }

        while (temp->next != nullptr) {
            if (list1->val < list2->val) {
                temp->next = list1;
                temp->val = list1->val;
                list1 = list1->next;
            } else {
                temp->next = list2;
                temp->val = list2->val;
                list2 = list2->next;
            }
        }
        return res;
    }
};

class Solution {
  public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        while (true) {
            if (list1 != nullptr && list2 != nullptr) {
                if (list1->val < list2->val) {
                    cur->next = list1;
                    cur = cur->next;
                    list1 = list1->next;
                } else {
                    cur->next = list2;
                    cur = cur->next;
                    list2 = list2->next;
                }
            } else if (list1 == nullptr) {
                cur->next = list2;
                break;
            } else {
                cur->next = list1;
                break;
            }
        }
        auto head = dummy->next;
        delete dummy;
        return head;
    }
};

int main() {
    Solution sol;
    string templateName = "Merge Two Sorted Lists";

    // 测试名向量
    vector<string> sn = {"Standard Case (Both lists have multiple elements)",
                         "Both Empty Lists", "One Empty List (L1 is empty)",
                         "One Empty List (L2 is empty)",
                         "Lists with Different Lengths and Overlapping Values"};

    // 测试数据定义
    vector<vector<int>> input1 = {{1, 2, 4}, {}, {}, {0}, {1, 5, 9}};
    vector<vector<int>> input2 = {{1, 3, 4}, {}, {0}, {}, {2, 4, 6, 8, 10}};
    vector<vector<int>> expected = {
        {1, 1, 2, 3, 4, 4}, {}, {0}, {0}, {1, 2, 4, 5, 6, 8, 9, 10}};

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        // 构建链表
        ListNode* l1 = createLinkedList(input1[i]);
        ListNode* l2 = createLinkedList(input2[i]);

        // 执行待测函数
        ListNode* resultNode = sol.mergeTwoLists(l1, l2);
        vector<int> resultVec = listToVector(resultNode);

        // 格式化输出
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

        // 注意：由于 merge 操作会复用原节点，手动管理内存需谨慎。
        // 这里仅作为模板，逻辑实现后需根据具体实现方式决定如何释放内存。
    }

    return 0;
}