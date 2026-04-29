// Created by Neuroil on 2026/04/10

/* * 题目：和为 K 的子数组 (Subarray Sum Equals K)
 * * 【题目描述】
 * 给你一个整数数组 nums 和一个整数 k ，请你统计并返回该数组中和为 k 的子数组的个数。
 * 子数组是数组中元素的连续非空序列。
 * * 【示例说明】
 * 示例 1:
 * 输入: nums = [1,1,1], k = 2
 * 输出: 2
 * 解释: [1,1] 出现两次。
 * * 示例 2:
 * 输入: nums = [1,2,3], k = 3
 * 输出: 2
 * 解释: [1,2] 和 [3] 为满足条件的子数组。
 * * 【提示】
 * - 1 <= nums.length <= 2 * 10^4
 * - -1000 <= nums[i] <= 1000
 * - -10^7 <= k <= 10^7
 * * 【进阶思考】
 * 注意数组中存在负数，这是否意味着滑动窗口（双指针）不再适用？
 * 能否通过“前缀和 + 哈希表”实现 O(n) 的时间复杂度？
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_map>

using namespace std;

class Solution_0 {  // 暴力法
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        int n = nums.size();
        
        // 外层循环确定子数组的结尾
        for (int start = 0; start < n; ++start) {
            int sum = 0;
            // 内层循环向前累加，计算所有以 start 结尾的子数组和
            for (int end = start; end >= 0; --end) {
                sum += nums[end];
                if (sum == k) {
                    count++;
                }
            }
        }
        return count;
    }
};

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1; // 初始化：前缀和为0出现了1次（处理从开头开始的子数组）
        int count = 0, pre = 0;
        for (int& x : nums) {
            pre += x; // 计算当前前缀和
            if (mp.count(pre - k)) {
                count += mp[pre - k]; // 如果 pre - k 存在，累加它出现的次数
            }
            mp[pre]++; // 记录当前前缀和出现的次数
        }
        return count;
    }
};

int main() {
    Solution sol;

    // 测试场景描述
    vector<string> sn = {
        "标准正数数组",
        "包含负数的数组",
        "全为零的特殊场景",
        "k 为 0 的场景",
        "单元素匹配与不匹配"
    };

    // 测试数据
    struct TestCase {
        vector<int> nums;
        int k;
        int expected;
    };

    vector<TestCase> cases = {
        {{1, 1, 1}, 2, 2},
        {{1, 2, 3}, 3, 2},
        {{1, -1, 0}, 0, 3}, // 子数组: [1,-1], [0], [1,-1,0]
        {{0, 0, 0}, 0, 6},   // 子数组: 3个单0, 2个双0, 1个三0
        {{-1}, -1, 1}
    };

    cout << "========== Subarray Sum Equals K 测试 ==========" << endl;

    for (int i = 0; i < (int)cases.size(); ++i) {
        int result = sol.subarraySum(cases[i].nums, cases[i].k);
        bool is_pass = (result == cases[i].expected);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    nums = [";
        for (size_t j = 0; j < cases[i].nums.size(); ++j) {
            cout << cases[i].nums[j] << (j == cases[i].nums.size() - 1 ? "" : ",");
        }
        cout << "], k = " << cases[i].k << endl;
        
        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << cases[i].expected << endl;
        cout << "  Status:   " << (is_pass ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}