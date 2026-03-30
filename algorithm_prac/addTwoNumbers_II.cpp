// Created by Neuroil on 2026/03/30

/* * 题目：两数相加 II (Add Two Numbers II)
 * * [题目要求]
 * 给你两个非空链表来代表两个非负整数。数字最高位位于链表开始位置。
 * 将这两个数相加会返回一个新的链表。
 * * [示例说明]
 * 示例 1：l1 = [7,2,4,3], l2 = [5,6,4] -> 输出 [7,8,0,7]
 * 示例 2：l1 = [2,4,3], l2 = [5,6,4] -> 输出 [8,0,7]
 * 示例 3：l1 = [0], l2 = [0]          -> 输出 [0]
 * * [提示与进阶]
 * 1. 链表长度范围 [1, 100]。
 * 2. 进阶：如果输入链表不能翻转该如何解决？
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 工具函数
ListNode* createList(vector<int> nums) {
    ListNode* dummy = new ListNode();
    ListNode* cur = dummy;
    for (int x : nums) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    return dummy->next;
}

vector<int> listToVec(ListNode* head) {
    vector<int> res;
    while (head) { res.push_back(head->val); head = head->next; }
    return res;
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 严禁在此处实现算法逻辑
        return nullptr;
    }
};

int main() {
    Solution sol;
    vector<string> sn = {"Normal addition", "Equal length with carry", "Single zero", "Large carry at head", "Different lengths"};
    vector<vector<int>> in1 = {{7,2,4,3}, {2,4,3}, {0}, {9,9}, {1}};
    vector<vector<int>> in2 = {{5,6,4}, {5,6,4}, {0}, {1}, {9,9}};
    vector<vector<int>> exp = {{7,8,0,7}, {8,0,7}, {0}, {1,0,0}, {1,0,0}};

    cout << "========== Add Two Numbers II 测试 ==========" << endl;
    for (int i = 0; i < sn.size(); ++i) {
        ListNode* res = sol.addTwoNumbers(createList(in1[i]), createList(in2[i]));
        vector<int> resV = listToVec(res);
        cout << "Test Case " << i+1 << " (" << sn[i] << "):\n  Result:   [";
        for(int j=0; j<resV.size(); ++j) cout << resV[j] << (j==resV.size()-1?"":",");
        cout << "]\n  Expected: [";
        for(int j=0; j<exp[i].size(); ++j) cout << exp[i][j] << (j==exp[i].size()-1?"":",");
        cout << "]\n  Status:   " << (resV == exp[i] ? "PASS" : "FAIL") << "\n----------------" << endl;
    }
    return 0;
}