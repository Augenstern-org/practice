// Created by Neuroil on 2026/04/11

/* * 题目：滑动窗口最大值 (Sliding Window Maximum)
 * * 【题目描述】
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
 * 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
 * 返回滑动窗口中的最大值。
 * * 【示例说明】
 * 示例 1:
 * 输入: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * 输出: [3,3,5,5,6,7]
 * 解释: 随着窗口滑动，每个阶段的最大值分别为 3, 3, 5, 5, 6, 7。
 * * 示例 2:
 * 输入: nums = [1], k = 1
 * 输出: [1]
 * * 【提示】
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * - 1 <= k <= nums.length
 * * 【进阶思考】
 * 1. 暴力法 $O(n \times k)$ 在 $10^5$ 数据量下会超时。
 * 2. 考虑使用“单调队列” (Monotonic Queue) 维护窗口内的候选最大值。
 * 3. 队列中应该存储元素本身还是存储索引？存储索引更方便判断窗口是否过期。
 */

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // 1. 声明一个空的双端队列（最常用）
        std::deque<int> dq; 

        // 2. 存储下标
        // 为什么要存下标？因为存下标可以方便地通过 nums[dq.front()] 拿到值，
        // 同时可以用 i - dq.front() >= k 来判断这个最大值是否已经滑出窗口了。

        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            // 1. 【删】：如果队首下标已经失效（滑出窗口），弹出
            if (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }

            // 2. 【进】：保持队列单调递减
            // 只要新元素 nums[i] 比队尾元素大，队尾就没用了，弹出
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);

            // 3. 【取】：当窗口形成（i >= k-1）时，队首就是当前窗口最大值的下标
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};

// 辅助函数：输出 vector
void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << (i == v.size() - 1 ? "" : ",");
    }
    cout << "]";
}

int main() {
    Solution sol;

    // 测试场景描述
    vector<string> sn = {
        "标准示例",
        "单元素数组",
        "窗口大小等于数组长度",
        "递减数组场景",
        "包含重复元素的场景"
    };

    struct TestCase {
        vector<int> nums;
        int k;
        vector<int> expected;
    };

    vector<TestCase> cases = {
        {{1, 3, -1, -3, 5, 3, 6, 7}, 3, {3, 3, 5, 5, 6, 7}},
        {{1}, 1, {1}},
        {{1, 2, 3}, 3, {3}},
        {{5, 4, 3, 2, 1}, 2, {5, 4, 3, 2}},
        {{1, 3, 1, 2, 0, 5}, 3, {3, 3, 2, 5}}
    };

    cout << "========== Sliding Window Maximum 测试 ==========" << endl;

    for (int i = 0; i < (int)cases.size(); ++i) {
        vector<int> result = sol.maxSlidingWindow(cases[i].nums, cases[i].k);
        bool is_pass = (result == cases[i].expected);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    nums = "; printVec(cases[i].nums); cout << ", k = " << cases[i].k << endl;
        cout << "  Result:   "; printVec(result); cout << endl;
        cout << "  Expected: "; printVec(cases[i].expected); cout << endl;
        cout << "  Status:   " << (is_pass ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}