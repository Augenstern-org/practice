// Created by Neuroil on 2026/03/31

/* * 题目：两数之和 (Two Sum)
 * * [题目要求]
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值
 * target 的那两个整数，并返回它们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 * * [示例说明]
 * 示例 1：nums = [2,7,11,15], target = 9 -> 输出 [0,1]
 * 示例 2：nums = [3,2,4], target = 6       -> 输出 [1,2]
 * 示例 3：nums = [3,3], target = 6         -> 输出 [0,1]
 * * [提示与进阶]
 * 1. 2 <= nums.length <= 10^4
 * 2. 只会存在一个有效答案。
 * 3. 进阶：你可以想出一个时间复杂度小于 O(n^2) 的算法吗？
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int f, s;
        for (int i = 0; i != nums.size(); ++i) {
            f = i;
            for (int j = 0; j != nums.size(); ++j) {
                if (j == i) continue;
                s = j;
                if (nums[i] + nums[j] == target) {
                    return {f, s};
                }
            }
        }
    }
};

class Solution2 {
  public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); i++) {
            int temp = target - nums[i];
            if (hashtable.count(temp)) {
                return {hashtable[temp], i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};

int main() {
    Solution sol;
    string templateName = "Two Sum";

    vector<string> sn = {"Standard Case", "Target is sum of middle elements",
                         "Last two elements", "Duplicate values as target",
                         "Negative numbers included"};

    vector<vector<int>> nums_list = {
        {2, 7, 11, 15}, {3, 2, 4}, {3, 3}, {1, 5, 5, 8}, {-1, -2, -3, -4, -5}};
    vector<int> targets = {9, 6, 6, 10, -8};
    vector<vector<int>> expecteds = {{0, 1}, {1, 2}, {0, 1}, {1, 2}, {2, 4}};

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        vector<int> result = sol.twoSum(nums_list[i], targets[i]);

        // 为了对比方便，对结果进行排序
        sort(result.begin(), result.end());

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    nums = [";
        for (int j = 0; j < nums_list[i].size(); ++j)
            cout << nums_list[i][j]
                 << (j == nums_list[i].size() - 1 ? "" : ",");
        cout << "], target = " << targets[i] << endl;

        cout << "  Result:   [";
        for (int j = 0; j < result.size(); ++j)
            cout << result[j] << (j == result.size() - 1 ? "" : ",");
        cout << "]" << endl;

        cout << "  Expected: [";
        for (int j = 0; j < expecteds[i].size(); ++j)
            cout << expecteds[i][j]
                 << (j == expecteds[i].size() - 1 ? "" : ",");
        cout << "]" << endl;

        bool isPass = (result == expecteds[i]);
        cout << "  Status:   "
             << (isPass ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}