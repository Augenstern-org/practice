// Created by Neuroil on 2026/04/01

/* * 题目：字母异位词分组 (Group Anagrams)
 * * [题目要求]
 * 给你一个字符串数组，请你将字母异位词组合在一起。可以按任意顺序返回结果列表。
 * 字母异位词指字母相同，但排列不同的字符串。
 * * [示例说明]
 * 示例 1: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
 * 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * * [提示]
 * 1. 1 <= strs.length <= 10^4
 * 2. 0 <= strs[i].length <= 100
 * 3. strs[i] 仅包含小写字母
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  public:
    // 缺点，仍旧容易发生哈希碰撞
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        std::vector<std::vector<std::string>> res;
        std::unordered_map<char, std::vector<std::string>> temp;
        for (auto& s : strs) {
            std::unordered_map<char, int> counter;
            for (auto c : s) {
                auto it = counter.find(c);
                if (it == counter.end()) {
                    counter[c] = 0;
                }
                ++counter[c];
            }
            char hash = 0;
            for (auto obj : counter) {
                hash ^= obj.first;
                hash ^= obj.second;
            }
            auto it = temp.find(hash);
            if (it == temp.end()) {
                temp[hash] = {};
            }
            temp[hash].push_back(s);
        }
        res.resize(temp.size());
        int c = 0;
        for (auto obj : temp) {
            for (int i = 0; i != obj.second.size(); ++i) {
                res[c].push_back(obj.second[i]);
            }
            ++c;
        }
        return res;
    }
};

class Solution2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // Key: 排序后的字符串 (指纹), Value: 对应的异或词集合
        unordered_map<string, vector<string>> mp;
        
        for (string& s : strs) {
            string key = s;
            sort(key.begin(), key.end()); // 排序：eat, tea, ate 都会变成 aet
            mp[key].push_back(s);         // 直接推入对应的组
        }
        
        vector<vector<string>> res;
        // 预分配空间，提升性能
        res.reserve(mp.size()); 
        
        for (auto& pair : mp) {
            // move 可以避免内存拷贝，直接“搬运” vector
            res.push_back(std::move(pair.second)); 
        }
        
        return res;
    }
};

// 辅助函数：对比二维 vector（忽略顺序）
bool compareResult(vector<vector<string>> res, vector<vector<string>> exp) {
    if (res.size() != exp.size()) return false;
    for (auto& v : res) sort(v.begin(), v.end());
    for (auto& v : exp) sort(v.begin(), v.end());
    sort(res.begin(), res.end());
    sort(exp.begin(), exp.end());
    return res == exp;
}

int main() {
    Solution sol;
    string templateName = "Group Anagrams";

    vector<string> sn = {
        "Standard Case", "Empty String", "Single Character",
        "No Anagrams",   "All Anagrams",
    };

    vector<vector<string>> inputs = {
        {"eat", "tea", "tan", "ate", "nat", "bat"},
        {""},
        {"a"},
        {"abc", "def", "ghi"},
        {"abc", "bca", "cab"},
    };

    vector<vector<vector<string>>> expecteds = {
        {{"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}},
        {{""}},
        {{"a"}},
        {{"abc"}, {"def"}, {"ghi"}},
        {{"abc", "bca", "cab"}},
    };

    cout << "========== " << templateName << " 测试 ==========" << endl;

    for (int i = 0; i < sn.size(); ++i) {
        vector<vector<string>> result = sol.groupAnagrams(inputs[i]);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input size: " << inputs[i].size() << endl;

        bool isPass = compareResult(result, expecteds[i]);
        cout << "  Status:     "
             << (isPass ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}