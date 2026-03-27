// Created by Neuroil on 2026/03/26
/*
    题目简述：柠檬水找零
    一杯柠檬水 5 美元。顾客支付 5, 10 或 20 美元。你初始有 0 元，需按顺序找零。
    如果能为所有顾客找零则返回 true，否则返回 false。

    示例：
    - bills = [5,5,5,10,20] -> true (找零逻辑：10给5，20给10+5)
    - bills = [5,5,10,10,20] -> false (最后一位无法找零 15 元)

    提示与进阶要求：
    1. 1 <= bills.length <= 10^5
    2. bills[i] 仅为 5, 10, 20。
    3. 贪心策略：找零 15 元时，优先使用 10+5 的组合，因为 5 元面值更灵活。
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    bool lemonadeChange(vector<int> &bills) {
        int five = 0, ten = 0;
        for (auto b : bills) {
            if(b == 5) ++five;
            else if(b == 10) ++ten;
            if (b == 10) {
                if (five == 0) {
                    return false;
                }
                --five;
            } else if (b == 20) {
                if (ten != 0 && five != 0) {
                    --five;
                    --ten;
                    continue;
                }
                if(five >= 3){
                    five -= 3;
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution sol;

    // 测试场景描述
    string s1 = "Simple success case";
    string s2 = "Fail at 20 dollar bill (insufficient 5s)";
    string s3 = "Fail at 10 dollar bill";
    string s4 = "Greedy choice needed (10+5 is better than 5+5+5)";
    string s5 = "All 5 dollar bills";

    vector<string> sn = {s1, s2, s3, s4, s5};

    // 测试用例数据
    struct TestCase {
        vector<int> bills;
        bool expected;
    };

    vector<TestCase> test_data = {{{5, 5, 5, 10, 20}, true},
                                  {{5, 5, 10, 10, 20}, false},
                                  {{10, 10}, false},
                                  {{5, 5, 5, 5, 10, 5, 10, 10, 10, 20}, true},
                                  {{5, 5, 5, 5}, true}};

    cout << "========== Lemonade Change 测试 ==========" << endl;

    for (int i = 0; i < test_data.size(); ++i) {
        vector<int> bills = test_data[i].bills;
        bool expected = test_data[i].expected;

        bool result = sol.lemonadeChange(bills);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    [ ";
        for (int b : bills)
            cout << b << " ";
        cout << "]" << endl;

        cout << "  Result:   " << (result ? "true" : "false") << endl;
        cout << "  Expected: " << (expected ? "true" : "false") << endl;
        cout << "  Status:   " << (result == expected ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}