// Created by Neuroil on 2026/03/26
/*
    题目简述：在区间 [low, high] 内统计奇数的数目。
    给定两个非负整数 low 和 high，返回该闭区间内奇数的个数。

    提示：
    1. 0 <= low <= high <= 10^9
    2. 进阶：尝试使用 O(1) 的时间复杂度解决，而不是循环遍历。
    3. 思路：[0, x] 之间的奇数个数可以通过 (x + 1) / 2 直接计算。
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 保持 Solution 类定义不变
class Solution {
public:
    int countOdds(int low, int high) {
        return (high + 1) / 2 - (low / 2);
    }
};

int main() {
    Solution sol;

    // 测试用字符串序列
    string s1 = "Both low and high are odd";
    string s2 = "Both low and high are even";
    string s3 = "Low is even, high is odd";
    string s4 = "Low is odd, high is even";
    string s5 = "Large range test";

    // 测试数据
    struct TestCase {
        int low;
        int high;
        int expected;
        string name;
    };

    vector<TestCase> testCases = {
        {3, 7, 3, s1},   // 3, 5, 7
        {8, 10, 1, s2},  // 9
        {4, 9, 3, s3},   // 5, 7, 9
        {5, 8, 2, s4},   // 5, 7
        {0, 1000000000, 500000000, s5}
    };

    cout << "========== CountOdds 测试 ==========" << endl;

    for (int i = 0; i < testCases.size(); ++i) {
        int low = testCases[i].low;
        int high = testCases[i].high;
        int expected = testCases[i].expected;
        
        int result = sol.countOdds(low, high);

        cout << "Test Case " << i + 1 << ": (" << testCases[i].name << ")" << endl;
        cout << "  Input:    low = " << low << ", high = " << high << endl;
        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected << endl;
        cout << "  Status:   " << (result == expected ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}