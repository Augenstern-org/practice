

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int sum = 0;
        for (int i = 0; i != s.size(); ++i){
            if (s[i] == 'I' && i != s.size()-1){
                switch (s[i+1])
                {
                case 'V':
                    sum += 4;
                    ++i;
                    break;
                case 'X':
                    sum += 9;
                    ++i;
                    break;
                default:
                    sum += 1;
                    break;
                }
            } else if (s[i] == 'X' && i != s.size()-1){
                switch (s[i+1])
                {
                case 'L':
                    sum += 40;
                    ++i;
                    break;
                case 'C':
                    sum += 90;
                    ++i;
                    break;
                default:
                    sum += 10;
                    break;
                }
            } else if (s[i] == 'C' && i != s.size()-1){
                switch (s[i+1])
                {
                case 'D':
                    sum += 400;
                    ++i;
                    break;
                case 'M':
                    sum += 900;
                    ++i;
                    break;
                default:
                    sum += 100;
                    break;
                }
            } else {
                switch (s[i])
                {
                case 'I':
                    sum += 1;
                    break;
                case 'V':
                    sum += 5;
                    break;
                case 'X':
                    sum += 10;
                    break;
                case 'L':
                    sum += 50;
                    break;
                case 'C':
                    sum += 100;
                    break;
                case 'D':
                    sum += 500;
                    break;
                case 'M':
                    sum += 1000;
                    break;
                default:
                    break;
                }
            }
        }
        return sum;
    }
};

int main() {
    // 测试用例（命名为 s1, s2, ...）
    std::string s1 = "III";
    std::string s2 = "IV";
    std::string s3 = "IX";
    std::string s4 = "LVIII";
    std::string s5 = "MCMXCIV";

    std::vector<std::string> test{s1, s2, s3, s4, s5};

    Solution sol;
    std::cout << "Roman to Integer Tests:\n";
    for (size_t i = 0; i < test.size(); ++i) {
        const std::string &s = test[i];
        // 注意：`romanToInt` 当前未实现，这里展示调用方式和输出格式
        int result = sol.romanToInt(s);
        std::cout << "Test " << (i + 1) << ": input = " << s
                  << "  -> output = " << result << endl;
    }

    return 0;
}

/*
    不是，这个写法真的好丑陋。这还能0ms 9.87MiB占用。
    那些十多ms和13MiB占用的是什么情况。
    感觉这道题没什么参考价值。
    官方是用哈希表实现的。不过这种数据量感觉没必要。
*/