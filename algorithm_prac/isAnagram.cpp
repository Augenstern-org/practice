#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        int s_size = s.size();
        // 0 -> 已用 | 1 -> 未用
        vector<bool> p(s_size * 2, 1);
        for(int i = 0; i != s_size; ++i){

            cout << "i:p[" << i << "]: " << p[i] << endl;

            p[i] = 0;
            for(int j = 0; j != s_size; ++j){

                cout << "j:p[" << s_size + j << "]: " << p[s_size + j] << endl;

                if (p[s_size + j] == 0){
                    continue;
                }
                if (s[i] == t[j]){
                    p[s_size + j] = 0;
                    break;
                }
            }
        }
        int check = 0;
        for(auto b : p){
            check += b;
            cout << "p:" << b;
        }
        cout << endl;
        if (check == 0) {return true;}
        return false;
    }
};

class Solution2 {
public:
    bool isAnagram(string s, string t) {
        char check = 0;
        for (auto c : s){
            check ^= c;
        }
        for (auto c : t){
            check ^= c;
        }
        if (check == 0){ return true;}
        return false;
    }
};

class SolutionFinal {
public:
    bool isAnagram(string s, string t) {
        vector<int> counter(26, 0);
        for (auto c : s){
            ++counter[c - 'a'];
        }
        for (auto c : t){
            --counter[c - 'a'];
        }
        for (auto c : counter){
            if (c != 0){
                return false;
            }
        }
        return true;
    }
};

int main(){
    SolutionFinal s;
    cout << s.isAnagram("rat", "car") << endl;
    return 0;
}

/*
题目考查点：判断两个字符串是否互为字母异位词（字母数量和种类是否相同）。
最优算法：计数数组（长度固定为26或字符集大小），一次遍历统计频次差，时间 O(n)，额外空间 O(1)。
时间复杂度：O(n)，n 为字符串长度。空间复杂度：O(1)（固定大小计数数组）。
实现可优化点：
 - 移除调试输出（当前实现中有大量 cout 打印，会严重影响性能和可读性）。
 - 若字符集非小写英文，可考虑使用 unordered_map<char,int> 或更大计数数组。
 - 注意输入合法性检查（空串、大小写敏感等）。
学习方向：哈希计数思想、排序法（O(n log n)）对比、字符串处理与字符编码问题。
*/