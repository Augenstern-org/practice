// Created by Neuroil on 2026/04/06

/*
题目：三数之和

给定一个整数数组 nums，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足：
1. i != j, i != k, 且 j != k
2. nums[i] + nums[j] + nums[k] == 0

请返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。

示例 1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0
不同的三元组是 [-1,0,1] 和 [-1,-1,2]
注意，输出的顺序和三元组的顺序并不重要

示例 2：
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0

示例 3：
输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0

提示：
3 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;

        int f_last = 100000, s_last = 100000;
        for (int i = 0; i != nums.size() - 2; ++i) {
            if (nums[i] == f_last) continue;
            f_last = nums[i];
            for (int j = i + 1; j != nums.size() - 1; ++j) {
                if (nums[j] == s_last) continue;
                s_last = nums[j];

                int temp = 0 - f_last - s_last;
                for (int u = j + 1; u != nums.size(); ++u) {
                    if (nums[u] == temp) {
                        res.push_back({f_last, s_last, temp});
                        break;
                    }
                }
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }
};

// 测试场景描述向量
vector<string> s1 = {
    "基础示例：包含正负数，有多个解",
    "无解情况：所有数都为正数",
    "全零数组：唯一解为[0,0,0]",
    "重复元素：需要去重",
    "边界情况：最小长度数组",
    "大数测试：包含边界值",
    "对称数组：正负数对称分布",
};

// 辅助函数：打印二维向量
void printVector2D(const vector<vector<int>>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j];
            if (j < vec[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < vec.size() - 1) cout << ",";
    }
    cout << "]";
}

// 辅助函数：比较两个二维向量是否相等（忽略顺序）
bool compareVectors(const vector<vector<int>>& v1,
                    const vector<vector<int>>& v2) {
    if (v1.size() != v2.size()) return false;

    // 简单实现：转换为字符串比较（实际使用时需要更严谨的比较逻辑）
    // 这里为了测试模板的简洁性，使用简单比较
    vector<string> s1, s2;
    for (const auto& vec : v1) {
        string s = "[";
        for (int num : vec) {
            s += to_string(num) + ",";
        }
        if (!vec.empty()) s.pop_back(); // 移除最后一个逗号
        s += "]";
        s1.push_back(s);
    }

    for (const auto& vec : v2) {
        string s = "[";
        for (int num : vec) {
            s += to_string(num) + ",";
        }
        if (!vec.empty()) s.pop_back();
        s += "]";
        s2.push_back(s);
    }

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    return s1 == s2;
}

int main() {
    Solution solution;

    cout << "========== 三数之和测试 ==========" << endl << endl;

    // 测试用例1：基础示例
    {
        cout << "Test Case 1 (" << s1[0] << "):" << endl;
        vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
        vector<vector<int>> expected1 = {{-1, -1, 2}, {-1, 0, 1}};

        cout << "Input:    [";
        for (size_t i = 0; i < nums1.size(); i++) {
            cout << nums1[i];
            if (i < nums1.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result1 = solution.threeSum(nums1);
        cout << "Result:   ";
        printVector2D(result1);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected1);
        cout << endl;

        bool pass1 = compareVectors(result1, expected1);
        cout << "Status:   " << (pass1 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例2：无解情况
    {
        cout << "Test Case 2 (" << s1[1] << "):" << endl;
        vector<int> nums2 = {1, 2, 3, 4, 5};
        vector<vector<int>> expected2 = {};

        cout << "Input:    [";
        for (size_t i = 0; i < nums2.size(); i++) {
            cout << nums2[i];
            if (i < nums2.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result2 = solution.threeSum(nums2);
        cout << "Result:   ";
        printVector2D(result2);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected2);
        cout << endl;

        bool pass2 = compareVectors(result2, expected2);
        cout << "Status:   " << (pass2 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例3：全零数组
    {
        cout << "Test Case 3 (" << s1[2] << "):" << endl;
        vector<int> nums3 = {0, 0, 0};
        vector<vector<int>> expected3 = {{0, 0, 0}};

        cout << "Input:    [";
        for (size_t i = 0; i < nums3.size(); i++) {
            cout << nums3[i];
            if (i < nums3.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result3 = solution.threeSum(nums3);
        cout << "Result:   ";
        printVector2D(result3);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected3);
        cout << endl;

        bool pass3 = compareVectors(result3, expected3);
        cout << "Status:   " << (pass3 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例4：重复元素
    {
        cout << "Test Case 4 (" << s1[3] << "):" << endl;
        vector<int> nums4 = {-1, -1, -1, 2, 2};
        vector<vector<int>> expected4 = {{-1, -1, 2}};

        cout << "Input:    [";
        for (size_t i = 0; i < nums4.size(); i++) {
            cout << nums4[i];
            if (i < nums4.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result4 = solution.threeSum(nums4);
        cout << "Result:   ";
        printVector2D(result4);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected4);
        cout << endl;

        bool pass4 = compareVectors(result4, expected4);
        cout << "Status:   " << (pass4 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例5：边界情况
    {
        cout << "Test Case 5 (" << s1[4] << "):" << endl;
        vector<int> nums5 = {0, 0, 0}; // 最小长度
        vector<vector<int>> expected5 = {{0, 0, 0}};

        cout << "Input:    [";
        for (size_t i = 0; i < nums5.size(); i++) {
            cout << nums5[i];
            if (i < nums5.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result5 = solution.threeSum(nums5);
        cout << "Result:   ";
        printVector2D(result5);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected5);
        cout << endl;

        bool pass5 = compareVectors(result5, expected5);
        cout << "Status:   " << (pass5 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例6：大数测试
    {
        cout << "Test Case 6 (" << s1[5] << "):" << endl;
        vector<int> nums6 = {100000, -100000, 0};
        vector<vector<int>> expected6 = {{-100000, 0, 100000}};

        cout << "Input:    [";
        for (size_t i = 0; i < nums6.size(); i++) {
            cout << nums6[i];
            if (i < nums6.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result6 = solution.threeSum(nums6);
        cout << "Result:   ";
        printVector2D(result6);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected6);
        cout << endl;

        bool pass6 = compareVectors(result6, expected6);
        cout << "Status:   " << (pass6 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例7：对称数组
    {
        cout << "Test Case 7 (" << s1[6] << "):" << endl;
        vector<int> nums7 = {-2, -1, 0, 1, 2};
        vector<vector<int>> expected7 = {{-2, 0, 2}, {-1, 0, 1}};

        cout << "Input:    [";
        for (size_t i = 0; i < nums7.size(); i++) {
            cout << nums7[i];
            if (i < nums7.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        vector<vector<int>> result7 = solution.threeSum(nums7);
        cout << "Result:   ";
        printVector2D(result7);
        cout << endl;

        cout << "Expected: ";
        printVector2D(expected7);
        cout << endl;

        bool pass7 = compareVectors(result7, expected7);
        cout << "Status:   " << (pass7 ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    cout << endl << "========== 测试完成 ==========" << endl;

    return 0;
}