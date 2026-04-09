// Created by Neuroil on 2026/04/09

/*
题目：找到字符串中所有字母异位词 (Find All Anagrams in a String)

【题目描述】
给定两个字符串 s 和 p，找到 s 中所有 p 的异位词的子串，返回这些子串的起始索引。
异位词指由相同字母重排列形成的字符串（包括相同的字符串）。

【示例说明】

示例 1:
输入: s = "cbaebabacd", p = "abc"
输出: [0, 6]
解释: 索引 0 处的 "cba" 和索引 6 处的 "bac" 均为 "abc" 的异位词。

示例 2:
输入: s = "abab", p = "ab"
输出: [0, 1, 2]

【提示】
1 <= s.length, p.length <= 3 * 10^4
s 和 p 仅包含小写字母

*/

/*
    滑动窗口（Sliding
   Window）这种思想在刚接触时确实不太直观。它本质上是一种**“减少重复计算”**的艺术。
    我们可以把原本“暴力”的搜索方式比作“每次都要推倒重来”，而滑动窗口则是“在移动中微调”。

    1. 什么时候该用滑动窗口？
        当你发现题目满足以下三个特征时，脑子里就要立刻拉响“滑动窗口”的警报：
            处理的对象是“连续”的：比如连续子数组、连续子串。
            窗口大小或状态有规律：
            固定窗口：窗口长度固定（如本题，长度始终为 p.size()）。
            变长窗口：寻找满足某个条件的“最长”或“最短”子串。
            重复计算严重：你发现指针 i
   每移动一步，内部都要重新遍历一遍刚才遍历过的大部分元素。

    2. 滑动窗口的核心口诀
        你可以把滑动窗口的操作总结为简单的四个步骤：“进、出、算、更”。
            进：右指针（或循环变量）向右移动，新元素进入窗口，更新窗口内的统计数据。
            出：当窗口不再满足条件（或超过固定长度）时，左指针向右移动，旧元素移出窗口，同时恢复统计数据。
            算：在窗口滑动的过程中，计算当前窗口是否符合题目要求。
            更：更新最终结果（如记录起始索引、最大长度等）。

============================ 代码示例 ============================

    void slidingWindow(string s, string t) {
        unordered_map<char, int> need, window;
        for (char c : t) need[c]++;

        int left = 0, right = 0;
        int valid = 0; // 记录窗口中满足条件的字符个数
        while (right < s.size()) {
            // a. 【进】：c 是将移入窗口的字符
            char c = s[right];
            right++; // 右移窗口
            // 进行窗口内数据的一系列更新...

            // b. 【出】：判断左侧窗口是否要收缩
            while (window_needs_shrink) { // 对于固定窗口，通常是 right - left >= p.size()
                char d = s[left];
                left++; // 左移窗口
                // 进行窗口内数据的一系列更新...
            }
            
            // c. 【算/更】：在这里更新最终答案
        }

============================ 代码示例 ============================

    滑动窗口就是为了解决“重复扫描”问题的。
    如果你发现代码里有一个内循环在不停地扫描已经看过的元素，
    试着问问自己：“我能不能只处理新增的那个，并减去刚离开的那个？”
    只要能做到这一点，就掌握了滑动窗口。
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution_0 { // 暴力法
  public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) return {};
        std::vector<int> res;
        std::vector<int> target(26, 0);
        for (auto c : p) {
            ++target[c - 'a'];
        }
        for (int i = 0; i != s.size() - p.size() + 1; ++i) {
            std::vector<int> count(26, 0);
            for (int j = 0; j != p.size(); ++j) {
                ++count[s[i + j] - 'a'];
            }
            if (count == target) res.push_back(i);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int s_len = s.size(), p_len = p.size();
        if (s_len < p_len) return {};

        vector<int> res;
        vector<int> target(26, 0);
        vector<int> window(26, 0);

        // 初始化第一个窗口和目标频次
        for (int i = 0; i < p_len; ++i) {
            target[p[i] - 'a']++;
            window[s[i] - 'a']++;
        }

        if (window == target) res.push_back(0);

        // 开始滑动
        for (int i = p_len; i < s_len; ++i) {
            window[s[i] - 'a']++;          // 右边界进一个
            window[s[i - p_len] - 'a']--;  // 左边界出一个
            
            if (window == target) {
                res.push_back(i - p_len + 1);
            }
        }

        return res;
    }
};


// 辅助函数：格式化输出 vector<int>
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << (i == v.size() - 1 ? "" : ", ");
    }
    cout << "]";
}

int main() {
    Solution sol;

    // 测试场景描述
    vector<string> sn = {"标准示例 1", "标准示例 2", "无匹配项场景",
                         "完全匹配且重叠场景", "单一字符重复场景"};

    // 测试输入
    struct TestCase {
        string s;
        string p;
        vector<int> expected;
    };

    vector<TestCase> cases = {{"cbaebabacd", "abc", {0, 6}},
                              {"abab", "ab", {0, 1, 2}},
                              {"hello", "world", {}},
                              {"aaaaa", "aa", {0, 1, 2, 3}},
                              {"af", "be", {}}};

    cout << "========== Find All Anagrams 测试 ==========" << endl;

    for (int i = 0; i < cases.size(); ++i) {
        vector<int> result = sol.findAnagrams(cases[i].s, cases[i].p);

        // 简单排序以防顺序不一致（尽管题目不要求顺序）
        sort(result.begin(), result.end());
        sort(cases[i].expected.begin(), cases[i].expected.end());

        bool is_pass = (result == cases[i].expected);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    s = \"" << cases[i].s << "\", p = \"" << cases[i].p
             << "\"" << endl;
        cout << "  Result:   ";
        printVector(result);
        cout << endl;
        cout << "  Expected: ";
        printVector(cases[i].expected);
        cout << endl;
        cout << "  Status:   " << (is_pass ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}