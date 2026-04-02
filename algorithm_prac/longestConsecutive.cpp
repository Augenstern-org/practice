// Created by Neuroil on 2026/04/02

/* * 题目：最长连续序列 (Longest Consecutive Sequence)
 * * [题目要求]
 * 给定一个未排序的整数数组 nums ，找出数字连续的最长序列的长度。
 * 设计并实现时间复杂度为 O(n) 的算法。
 * * [示例说明]
 * 示例 1：nums = [100,4,200,1,3,2] -> 输出 4 ([1, 2, 3, 4])
 * 示例 2：nums = [0,3,7,2,5,8,4,6,0,1] -> 输出 9
 * * [提示]
 * 1. 0 <= nums.length <= 10^5
 * 2. -10^9 <= nums[i] <= 10^9
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    int longestConsecutive(vector<int>& nums) {
        int size = nums.size();
        if (size == 0) return 0;
        if (size == 1) return 1;
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        int max_len = 1;
        int init = 0;
        int counter = 1;
        auto end = nums_set.end();
        while (nums_set.find(init) == end) ++init;
        int temp = 1;
        for (int i = 1; counter == size; ++i) {
            if (nums_set.find(init + i) != end) {
                ++temp;
                ++counter;
            } else {
                if (temp > max_len) max_len = temp;
                temp = 1;
            }
        }
        return max_len;
    }
};

class Solution2 {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set(nums.begin(), nums.end());
        int max_len = 0;

        for (int num : num_set) {
            if (num_set.find(num - 1) == num_set.end()) {
                int currentNum = num;
                int currentLen = 1;

                while (num_set.find(currentNum + 1) != num_set.end()) {
                    currentNum += 1;
                    currentLen += 1;
                }

                max_len = max(max_len, currentLen);
            }
        }
        
        return max_len;
    }
};

int main() {
    Solution sol;
    string templateName = "Longest Consecutive Sequence";

    vector<string> sn = {"Standard Case", "Multiple sequences",
                         "Duplicates in array", "Empty array",
                         "Single element"};

    vector<vector<int>> inputs = {{100, 4, 200, 1, 3, 2},
                                  {0, 3, 7, 2, 5, 8, 4, 6, 0, 1},
                                  {1, 0, 1, 2},
                                  {},
                                  {10}};

    vector<int> expecteds = {4, 9, 3, 0, 1};

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        int result = sol.longestConsecutive(inputs[i]);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input size: " << inputs[i].size() << endl;
        cout << "  Result:     " << result << endl;
        cout << "  Expected:   " << expecteds[i] << endl;

        bool isPass = (result == expecteds[i]);
        cout << "  Status:     "
             << (isPass ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}