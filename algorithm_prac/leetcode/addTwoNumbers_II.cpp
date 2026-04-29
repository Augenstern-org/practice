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

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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
    while (head) {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

class Solution {
  private:
    inline std::vector<int>* listToVec(ListNode* l1) {
        std::vector<int>* res = new std::vector<int>;
        while (l1 != nullptr) {
            res->push_back(l1->val);
            l1 = l1->next;
        }
        reverse(res->begin(), res->end());
        return res;
    }

  public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto l1_pvec = listToVec(l1);
        auto l2_pvec = listToVec(l2);
        int len = l1_pvec->size() > l2_pvec->size() ? l1_pvec->size()
                                                    : l2_pvec->size();
        std::vector<int> res_vec(len, 0);
        int carry = 0;
        for (int i = 0; i != len; ++i) {
            int l1_val = 0, l2_val = 0, sum = 0;
            if (i < l1_pvec->size()) l1_val = (*l1_pvec)[i];
            if (i < l2_pvec->size()) l2_val = (*l2_pvec)[i];
            sum = l1_val + l2_val + carry;
            res_vec[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry > 0) res_vec.push_back(carry);
        ListNode* head = new ListNode();
        ListNode* cur = head;
        for (int i = res_vec.size() - 1; i > 0; --i) {
            ListNode* next = new ListNode();
            cur->val = res_vec[i];
            cur->next = next;
            cur = next;
        }
        cur->val = res_vec[0];
        cur->next = nullptr;
        delete l1_pvec;
        delete l2_pvec;
        return head;
    }
};

int main() {
    Solution sol;
    vector<string> sn = {"Normal addition", "Equal length with carry",
                         "Single zero", "Large carry at head",
                         "Different lengths"};
    vector<vector<int>> in1 = {{7, 2, 4, 3}, {2, 4, 3}, {0}, {9, 9}, {1}};
    vector<vector<int>> in2 = {{5, 6, 4}, {5, 6, 4}, {0}, {1}, {9, 9}};
    vector<vector<int>> exp = {
        {7, 8, 0, 7}, {8, 0, 7}, {0}, {1, 0, 0}, {1, 0, 0}};

    cout << "========== Add Two Numbers II 测试 ==========" << endl;
    for (int i = 0; i < sn.size(); ++i) {
        ListNode* res =
            sol.addTwoNumbers(createList(in1[i]), createList(in2[i]));
        vector<int> resV = listToVec(res);
        cout << "Test Case " << i + 1 << " (" << sn[i] << "):\n  Result:   [";
        for (int j = 0; j < resV.size(); ++j)
            cout << resV[j] << (j == resV.size() - 1 ? "" : ",");
        cout << "]\n  Expected: [";
        for (int j = 0; j < exp[i].size(); ++j)
            cout << exp[i][j] << (j == exp[i].size() - 1 ? "" : ",");
        cout << "]\n  Status:   " << (resV == exp[i] ? "PASS" : "FAIL")
             << "\n----------------" << endl;
    }
    return 0;
}