// Created by Neuroil on 2026/03/28
/*
    题目简述：二进制求和
    给你两个二进制字符串 a 和 b，返回它们的二进制和。

    示例：
    - a = "11", b = "1" -> "100"
    - a = "1010", b = "1011" -> "10101"

    提示与进阶要求：
    1. 1 <= a.length, b.length <= 10^4
    2. 字符串仅含 '0' 或 '1'，无前导零（除非是 "0"）。
    3. 思考：如何在一个循环内处理长度不一的两个字符串？
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    string addBinary(string a, string b) {
        int al = a.size() - 1;
        int bl = b.size() - 1;
        bool carry = 0;
        std::string res;
        while (al >= 0 || bl >= 0 || carry) {
            int x = (al >= 0) ? a[al--] - '0' : 0;
            int y = (bl >= 0) ? b[bl--] - '0' : 0;

            int sum = x ^ y ^ carry;
            carry = (x & y) | (carry & (x ^ y));

            res.push_back(sum + '0');
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution sol;

    // 测试场景描述
    string s1 = "Simple case without carry";
    string s2 = "Case with carry at the end";
    string s3 = "Different lengths";
    string s4 = "Both strings are zero";
    string s5 = "Long strings with multiple carries";

    vector<string> sn = {s1, s2, s3, s4, s5};

    // 测试用例数据
    struct TestCase {
        string a;
        string b;
        string expected;
    };

    vector<TestCase> test_data = {{"1010", "101", "1111"},
                                  {"11", "1", "100"},
                                  {"1", "111", "1000"},
                                  {"0", "0", "0"},
                                  {"1010", "1011", "10101"}};

    cout << "========== Add Binary 测试 ==========" << endl;

    for (int i = 0; i < test_data.size(); ++i) {
        string a = test_data[i].a;
        string b = test_data[i].b;
        string expected = test_data[i].expected;

        string result = sol.addBinary(a, b);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    a = \"" << a << "\", b = \"" << b << "\"" << endl;
        cout << "  Result:   \"" << result << "\"" << endl;
        cout << "  Expected: \"" << expected << "\"" << endl;
        cout << "  Status:   " << (result == expected ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}