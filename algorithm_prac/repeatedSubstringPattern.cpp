#include <iostream>
#include <string>
#include <vector>

using namespace std;

string s1 = "abab";                                     // 1
string s2 = "aba";                                      // 0
string s3 = "abcabcabcabc";                             // 1
string s4 = "qwertyuiopqwertyuiopqwertyuiop";           // 1
string s5 = "qwertyuioplkjhgfdsaqwertyuioplkjhgfds";    // 0

vector<string> test{s1, s2, s3, s4, s5};

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int s_len = s.size();
        for (int i = 1; i*2 <= s_len; ++i){
            if (s_len % i == 0){
                bool is_match = 1;
                for (int j = i; j != s_len; ++j){
                    if (s[j] != s[j-i]){
                        is_match = 0;
                        break;
                    }
                }
                if (is_match){
                    return true;
                }
            }
        }
        return false;
    }
};

int main(){
    Solution s;
    for(auto t : test){
        cout << "Result: " << s.repeatedSubstringPattern(t) << endl;
    }
}

/*
题目考查点：判断字符串是否由某个子串重复多次组成，考察字符串匹配与模式重复检测。
最优算法：可以使用字符串技巧 "(s + s).find(s, 1) != n"（时间 O(n)） 或 KMP 获取最长相等前后缀来判断，均可在线性时间内完成。
当前实现：对每个可能长度 i 做逐字符比较，最坏情况时间复杂度为 O(n^2)，对于长字符串性能不佳。
时间复杂度：最优 O(n)。当前实现最坏 O(n^2)。空间复杂度：O(1)（除输入外）。
实现可优化点：
 - 推荐使用 (s + s) 的技巧或构造 KMP 的 lps（前缀函数）来将复杂度降到 O(n)。
 - 注意避免重复字符串拼接导致额外开销（使用 find 时注意实现细节）。
学习方向：KMP 算法、字符串模式匹配技巧、字符串操作的时间/空间权衡。
*/