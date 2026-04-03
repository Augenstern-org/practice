// Created by Neuroil on 2026/04/03

/*
题目：盛最多水的容器

题目要求：
给定一个长度为 n 的整数数组 height。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i])。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。

示例说明：
示例 1：
输入：[1,8,6,2,5,4,8,3,7]
输出：49
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。
在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

示例 2：
输入：height = [1,1]
输出：1

提示：
n == height.length
2 <= n <= 10^5
0 <= height[i] <= 10^4

进阶要求：
尝试设计一个时间复杂度为 O(n) 的解决方案。
*/

// api: sk-f89a020f07054b2eac8bb52f07491647

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // 此处应保持空白，严禁剧透算法逻辑
        return 0;
    }
};

// 测试场景描述向量
vector<string> sn = {
    "基础测试 - 两个相同高度的柱子",
    "基础测试 - 递增高度",
    "经典示例 - 最大面积在中间",
    "复杂测试 - 多个峰值",
    "边界测试 - 大数组",
    "随机测试 - 混合高度"
};

int main() {
    Solution solution;
    
    cout << "========== 盛最多水的容器测试 ==========" << endl << endl;
    
    // 测试用例1
    cout << "Test Case 1 (" << sn[0] << "):" << endl;
    vector<int> height1 = {1, 1};
    int result1 = solution.maxArea(height1);
    int expected1 = 1;
    cout << "Input:    [1, 1]" << endl;
    cout << "Result:   " << result1 << endl;
    cout << "Expected: " << expected1 << endl;
    cout << "Status:   " << (result1 == expected1 ? "PASS" : "FAIL") << endl;
    cout << "------------------------------------" << endl;
    
    // 测试用例2
    cout << "Test Case 2 (" << sn[1] << "):" << endl;
    vector<int> height2 = {1, 2, 3, 4, 5};
    int result2 = solution.maxArea(height2);
    int expected2 = 4;
    cout << "Input:    [1, 2, 3, 4, 5]" << endl;
    cout << "Result:   " << result2 << endl;
    cout << "Expected: " << expected2 << endl;
    cout << "Status:   " << (result2 == expected2 ? "PASS" : "FAIL") << endl;
    cout << "------------------------------------" << endl;
    
    // 测试用例3
    cout << "Test Case 3 (" << sn[2] << "):" << endl;
    vector<int> height3 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int result3 = solution.maxArea(height3);
    int expected3 = 49;
    cout << "Input:    [1, 8, 6, 2, 5, 4, 8, 3, 7]" << endl;
    cout << "Result:   " << result3 << endl;
    cout << "Expected: " << expected3 << endl;
    cout << "Status:   " << (result3 == expected3 ? "PASS" : "FAIL") << endl;
    cout << "------------------------------------" << endl;
    
    // 测试用例4
    cout << "Test Case 4 (" << sn[3] << "):" << endl;
    vector<int> height4 = {3, 1, 2, 4, 5, 2, 6, 1, 3};
    int result4 = solution.maxArea(height4);
    int expected4 = 20;  // 高度6和高度5，距离4，面积=4*min(6,5)=20
    cout << "Input:    [3, 1, 2, 4, 5, 2, 6, 1, 3]" << endl;
    cout << "Result:   " << result4 << endl;
    cout << "Expected: " << expected4 << endl;
    cout << "Status:   " << (result4 == expected4 ? "PASS" : "FAIL") << endl;
    cout << "------------------------------------" << endl;
    
    // 测试用例5
    cout << "Test Case 5 (" << sn[4] << "):" << endl;
    vector<int> height5 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result5 = solution.maxArea(height5);
    int expected5 = 25;
    cout << "Input:    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]" << endl;
    cout << "Result:   " << result5 << endl;
    cout << "Expected: " << expected5 << endl;
    cout << "Status:   " << (result5 == expected5 ? "PASS" : "FAIL") << endl;
    cout << "------------------------------------" << endl;
    
    // 测试用例6
    cout << "Test Case 6 (" << sn[5] << "):" << endl;
    vector<int> height6 = {2, 3, 4, 5, 18, 17, 6};
    int result6 = solution.maxArea(height6);
    int expected6 = 17;  // 高度18和高度17，距离1，面积=17
    cout << "Input:    [2, 3, 4, 5, 18, 17, 6]" << endl;
    cout << "Result:   " << result6 << endl;
    cout << "Expected: " << expected6 << endl;
    cout << "Status:   " << (result6 == expected6 ? "PASS" : "FAIL") << endl;
    cout << "------------------------------------" << endl;
    
    cout << endl << "========== 测试完成 ==========" << endl;
    
    return 0;
}