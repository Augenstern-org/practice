// Created by Neuroil on 2026/04/08
/*
题目：无重复字符的最长子串（长度）

给定一个字符串 s ，请你找出其中不含有重复字符的最长子串的长度。

要求：实现一个 `Solution` 类及其方法 `lengthOfLongestSubstring`。
注意：在此模板中严禁实现算法逻辑，函数体必须保持空白或仅返回默认值以保证可编译。

示例：
  示例 1: 输入: s = "abcabcbb"  输出: 3  （最长子串为 "abc"）
  示例 2: 输入: s = "bbbbb"     输出: 1  （最长子串为 "b"）
  示例 3: 输入: s = "pwwkew"    输出: 3  （最长子串为 "wke"）

提示：
  0 <= s.length <= 5 * 10^4
  s 由英文字母、数字、符号和空格组成

进阶（提示，仅供阅读，不得在函数中实现）：
  - 可以使用滑动窗口 + 哈希表在 O(n) 时间内求解。
  - 也可以使用索引数组记录上次出现位置以优化常数因子。
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution_0 {
  public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        for (int j = 0; j != s.size(); ++j) {
        }
        for (int i = 0; i != s.size();) {
            std::unordered_set<int> chars;
            int counter = 0;
            for (; i != s.size(); ++i) {
                auto it = chars.end();
                if (chars.find(s[i]) == it) {
                    chars.insert(s[i]);
                    ++counter;
                    continue;
                }
                if (counter > res) res = counter;
                // char temp = s[i];
                // --i;
                // while(temp != s[i]) --i;
                // ++i;
                break;
            }
        }
        return res;
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::unordered_map<char, int> chars_map;
        int res = 0;
        int left_bound = 0;

        for (int right = 0; right < s.size(); ++right) {
            if (chars_map.find(s[right]) != chars_map.end()) {
                left_bound = max(left_bound, chars_map[s[right]] + 1);
            }
            chars_map[s[right]] = right;
            res = max(res, right - left_bound + 1);
        }
        return res;
    }
};

int main() {
    Solution sol;

    // 测试场景描述（至少 5 个）
    vector<string> sn = {
        "示例1：基本重复（abcabcbb）",
        "示例2：全部相同字符（bbbbb）",
        "示例3：重复但有最长子串（pwwkew）",
        "空字符串",
        "混合字符示例（dvdf）",
    };

    // 对应的输入参数和手工准备的期望值
    vector<string> inputs = {"abcabcbb", "bbbbb", "pwwkew", "", "dvdf"};
    vector<int> expected = {3, 1, 3, 0, 3};

    const string testName = "lengthOfLongestSubstring";
    cout << "========== " << testName << " 测试 ==========" << endl;

    size_t n = min(sn.size(), min(inputs.size(), expected.size()));
    for (size_t i = 0; i < n; ++i) {
        cout << "Test Case " << (i + 1) << " (" << sn[i] << "):" << endl;
        cout << "  Input:    " << inputs[i] << endl;

        int result = sol.lengthOfLongestSubstring(inputs[i]);

        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected[i] << endl;
        cout << "  Status:   " << (result == expected[i] ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}
