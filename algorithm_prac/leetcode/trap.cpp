// Created by Neuroil on 2026/04/07

/*
题目：接雨水

题目要求：
给定 n 个非负整数表示每个宽度为 1
的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例说明：
示例 1：
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接
6 个单位的雨水（蓝色部分表示雨水）。

示例 2：
输入：height = [4,2,0,3,2,5]
输出：9

提示：
n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5

进阶要求：
尝试使用 O(n) 时间复杂度和 O(1) 空间复杂度解决此问题。
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution_0 {
  public:
    int trap(vector<int>& height) {
        int max_area = 0;
        int temp_area = 0;
        int temp_height = 0;
        for (int i = 0; i != height.size() - 1; ++i) {
            if (height[i] >= temp_height) {
                temp_area += height[i] - temp_height;
                if (temp_area > max_area) max_area += temp_area;
                temp_area = 0;
            }
            temp_area += temp_height - height[i];
        }
        return max_area;
    }
};

class Solution {
  public:
    int trap(vector<int>& height) {
        int area = 0;
        int highest = 0;
        int len = height.size();
        // 确定最高层数
        for (auto h : height) {
            if (h > highest) highest = h;
        }
        // 遍历每一层，求每一层能积多少水，然后累加
        for (int i = 0; i < highest; ++i) {
            int start_pos = 0;
            while (start_pos != len && height[start_pos] == 0) ++start_pos; // 跳过前置0
            // start_pos 指向第一个非0位
            int temp = 0;
            for (int j = start_pos; j != len - 1; ++j) {
                // 空缺则可以接水，累加面积
                if (height[j] == 0) ++temp;
                // 凸起则将围起来的面积记入总面积
                else {
                    area += temp;
                    temp = 0;
                }
            }
            // 检验最后一位是不是墙，如果是则累加，不是那么不能积水
            if (height[len - 1] != 0) area += temp;
            // 遍历下一层
            for (auto& h : height) {
                if (h != 0) --h;
            }
        }
        return area;
    }
};

class Solution2 {
  public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;

        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0;
        int area = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) left_max = height[left];
                else area += left_max - height[left];
                ++left;
            } else {
                if (height[right] >= right_max) right_max = height[right];
                else area += right_max - height[right];
                --right;
            }
        }

        return area;
    }
};

// 测试场景描述向量
vector<string> sn = {
    "基础测试：简单山谷形状", "边界测试：单峰形状", "复杂测试：多峰多谷",
    "极端测试：递增序列",     "极端测试：递减序列", "示例测试1:题目示例1",
    "示例测试2:题目示例2",
};

int main() {
    Solution2 solution;

    cout << "========== 接雨水测试模板 ==========" << endl << endl;

    // 测试用例1：简单山谷形状
    {
        cout << "Test Case 1 (" << sn[0] << "):" << endl;
        vector<int> height = {2, 0, 2};
        int result = solution.trap(height);
        int expected = 2;
        cout << "Input:    [2, 0, 2]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例2：边界测试：单峰形状
    {
        cout << "Test Case 2 (" << sn[1] << "):" << endl;
        vector<int> height = {0, 1, 0};
        int result = solution.trap(height);
        int expected = 0;
        cout << "Input:    [0, 1, 0]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例3：复杂测试：多峰多谷
    {
        cout << "Test Case 3 (" << sn[2] << "):" << endl;
        vector<int> height = {3, 0, 2, 0, 4};
        int result = solution.trap(height);
        int expected = 7;
        cout << "Input:    [3, 0, 2, 0, 4]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例4：极端测试：递增序列
    {
        cout << "Test Case 4 (" << sn[3] << "):" << endl;
        vector<int> height = {1, 2, 3, 4, 5};
        int result = solution.trap(height);
        int expected = 0;
        cout << "Input:    [1, 2, 3, 4, 5]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例5：极端测试：递减序列
    {
        cout << "Test Case 5 (" << sn[4] << "):" << endl;
        vector<int> height = {5, 4, 3, 2, 1};
        int result = solution.trap(height);
        int expected = 0;
        cout << "Input:    [5, 4, 3, 2, 1]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例6：示例测试1
    {
        cout << "Test Case 6 (" << sn[5] << "):" << endl;
        vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        int result = solution.trap(height);
        int expected = 6;
        cout << "Input:    [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    // 测试用例7：示例测试2
    {
        cout << "Test Case 7 (" << sn[6] << "):" << endl;
        vector<int> height = {4, 2, 0, 3, 2, 5};
        int result = solution.trap(height);
        int expected = 9;
        cout << "Input:    [4, 2, 0, 3, 2, 5]" << endl;
        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected << endl;
        cout << "Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    cout << endl << "测试完成！" << endl;

    return 0;
}