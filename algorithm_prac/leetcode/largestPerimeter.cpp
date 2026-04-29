// Created by Neuroil on 2026/03/27
/*
    题目简述：三角形的最大周长
    给定由一些正数组成的数组
   nums，返回由其中三个长度组成的、面积不为零的三角形的最大周长。
    如果不能形成任何三角形，返回 0。

    示例：
    - nums = [2,1,2] -> 输出 5 (1,2,2 满足条件)
    - nums = [1,2,1,10] -> 输出 0

    提示与进阶要求：
    1. 3 <= nums.length <= 10^4
    2. 1 <= nums[i] <= 10^6
    3. 思考：为什么排序后只需要检查相邻的三个数？
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    /*
        对于数组 a, b, c,...，w, x, y, z
        首先应尝试倒数三个数x, y, z
            若满足x + y > z，则说明该组合全局最大
            若不满足则说明连除z以外最大的两个数都无法使条件成立
        接下来尝试w, x, y三个数即可
    */
    int largestPerimeter(vector<int> &nums) {
        if (nums.size() < 3) return 0;
        std::sort(nums.begin(), nums.end());
        for (int i = nums.size() - 1; i >= 2; --i) {
            if (nums[i] < nums[i - 1] + nums[i - 2])
                return nums[i] + nums[i - 1] + nums[i - 2];
        }
        return 0;
    }
};

int main() {
    Solution sol;

    // 测试场景描述
    string s1 = "Standard success case";
    string s2 = "Impossible to form triangle";
    string s3 = "Multiple options (choose largest)";
    string s4 = "Array with many small and one giant element";
    string s5 = "Minimum length array";

    vector<string> sn = {s1, s2, s3, s4, s5};

    // 测试用例数据
    struct TestCase {
        vector<int> nums;
        int expected;
    };

    vector<TestCase> test_data = {
        {{2, 1, 2}, 5},
        {{1, 2, 1, 10}, 0},
        {{3, 2, 3, 4}, 10}, // 可以是 2,3,4(9) 或 3,3,4(10)，选大的
        {{1, 2, 1, 100, 50, 60}, 210},
        {{3, 6, 2}, 0}};

    cout << "========== Largest Perimeter 测试 ==========" << endl;

    for (int i = 0; i < test_data.size(); ++i) {
        vector<int> nums = test_data[i].nums;
        int expected = test_data[i].expected;

        // 复制一份数据，防止某些实现修改了原数组影响观察
        vector<int> input_copy = nums;
        int result = sol.largestPerimeter(nums);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    [ ";
        for (int n : input_copy)
            cout << n << " ";
        cout << "]" << endl;

        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected << endl;
        cout << "  Status:   " << (result == expected ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}