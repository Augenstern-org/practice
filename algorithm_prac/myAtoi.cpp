// Created by Neuroil on 2026/03/31

/* * 题目：字符串转换整数 (atoi)
 * * [算法流程]
 * 1. 空格：丢弃无用的前导空格。
 * 2. 符号：检查下一个字符为 '-' 或 '+'，确定正负。
 * 3. 转换：读取数字直到遇到非数字字符，跳过前置零。
 * 4. 舍入：若超过 [−2^31, 2^31 − 1] 范围，则截断为边界值。
 * * [示例说明]
 * 示例 1："42" -> 42
 * 示例 2：" -042" -> -42
 * 示例 3："1337c0d3" -> 1337
 * 示例 4："0-1" -> 0
 * 示例 5："words and 987" -> 0
 * * [提示]
 * 0 <= s.length <= 200
 * s 由字母、数字、空格、'+'、'-'、'.' 组成。
 */

#include <climits> // 包含 INT_MAX 和 INT_MIN
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int find(string s) {
        int i = 0;
        int n = s.length();
        int sign = 1;
        int res = 0;

        // 1. 丢弃前导空格
        while (i < n && s[i] == ' ') {
            i++;
        }

        // 2. 检查符号
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        // 3. 转换数字并处理溢出
        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';

            // 4. 核心：溢出检查
            // 如果 res > 214748364，或者等于该值且下一位大于 7/8
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }

            res = res * 10 + digit;
            i++;
        }

        return res * sign;
    }
};

class Solution2 {
public:
    int myAtoi(string s) {
        int i = 0, n = s.size();

        // 1. 处理空格
        while (i < n && s[i] == ' ') {
            i++;
        }

        // 2. 处理符号
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') sign = -1;
            i ++;
        }
        
        // 3. 处理数字
        long num = 0; // 防溢出
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            int digit = s[i] - '0';
            if (num > (INT_MAX - digit) / 10) {
                return sign == 1 ? INT_MAX : INT_MIN;
            }
            num = num * 10 + digit;
            i++;
        }

        return sign * num;
    }
};

int main() {
    Solution sol;
    string templateName = "String to Integer (atoi)";

    vector<string> sn = {"Simple integer",          "Leading spaces and zeros",
                         "Mixed characters",        "Out of range (Positive)",
                         "Out of range (Negative)", "Invalid start"};

    vector<string> inputs = {"42",          "   -042",      "1337c0d3",
                             "91283472332", "-91283472332", "words and 987"};

    vector<int> expecteds = {42,
                             -42,
                             1337,
                             2147483647,  // INT_MAX
                             -2147483648, // INT_MIN
                             0};

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        int result = sol.find(inputs[i]);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    \"" << inputs[i] << "\"" << endl;
        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expecteds[i] << endl;

        bool isPass = (result == expecteds[i]);
        cout << "  Status:   "
             << (isPass ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}