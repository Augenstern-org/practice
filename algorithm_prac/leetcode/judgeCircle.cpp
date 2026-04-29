#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    bool judgeCircle(string moves) {
        std::vector<int> count(4, 0);
        for (auto c : moves) {
            if (c == 'U')
                ++count[0];
            else if (c == 'D')
                ++count[1];
            else if (c == 'L')
                ++count[2];
            else
                ++count[3];
        }
        if (count[0] == count[1] && count[2] == count[3]) return true;
        return false;
    }
};

class Solution2 {
public:
    bool judgeCircle(string moves) {
        int l = 0, u = 0,  len = moves.size();
        if(len % 2 == 1){   // 这一步挺聪明的
            return false;
        }
        for(auto x : moves){
            if(x == 'R'){
                l--;
            }else if(x == 'L'){
                l++;
            }else if(x == 'U'){
                u++;
            }else{
                u--;
            }
        }
        if(l == 0 && u == 0){
            return true;
        }
        return false;
    }
};

int main() {
    Solution solution;

    // 定义 5 个测试用例：sn，n 为正整数
    string s1 = "UD";       // 回到原点
    string s2 = "LL";       // 没回到原点
    string s3 = "RRDDLUUL"; // 复杂的回到原点路径
    string s4 = "UURDL";    // 没回到原点
    string s5 = "LDRU";     // 矩形路径回到原点

    vector<string> test_cases = {s1, s2, s3, s4, s5};

    cout << "========== 机器人能否返回原点测试 ==========" << endl;
    cout << "格式: [输入字符串] -> [预期结果] | [实际结果]" << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < test_cases.size(); ++i) {
        string moves = test_cases[i];
        bool result = solution.judgeCircle(moves);

        // 设定预期结果以便对比
        bool expected = false;
        // 简单的手动逻辑判断预期值（仅供测试展示）
        int v = 0, h = 0;
        for (char c : moves) {
            if (c == 'U')
                v++;
            else if (c == 'D')
                v--;
            else if (c == 'R')
                h++;
            else if (c == 'L')
                h--;
        }
        expected = (v == 0 && h == 0);

        cout << "s" << (i + 1) << ": \"" << moves << "\""
             << " -> Expected: " << (expected ? "true " : "false")
             << " | Actual: " << (result ? "true " : "false")
             << (expected == result ? " [OK]" : " [FAIL]") << endl;
    }

    return 0;
}