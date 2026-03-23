#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // 用于格式化输出

class Solution {
public:
    std::string toLowerCase(std::string s) {
        // 此处不实现具体逻辑，仅保留声明
        for (char &c : s) {
            if (c >= 'A' && c <= 'Z') {
                c += 32;
            }
        }
        return s;
    }
};

int main() {
    Solution solution;

    // 定义测试用例向量 sn
    std::string s1 = "Hello";
    std::string s2 = "here";
    std::string s3 = "LOVELY";
    std::string s4 = "123&^@ABC";
    std::string s5 = "pytHON_3.10";

    std::vector<std::string> test_cases = {s1, s2, s3, s4, s5};

    // 打印测试表头
    std::cout << std::setw(15) << "Input" << " | " << "Output" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // 执行测试逻辑
    for (int i = 0; i < test_cases.size(); ++i) {
        std::string input = test_cases[i];
        std::string result = solution.toLowerCase(input);

        // 格式化输出结果
        std::cout << "Test Case " << (i + 1) << ": " 
                  << std::setw(8) << "\"" << input << "\"" 
                  << " -> " 
                  << "\"" << result << "\"" << std::endl;
    }

    return 0;
}

