// Created by Neuroil on 2026/03/28
/*
    题目简述：字符串相乘 (Big Number Multiplication)
    给定两个以字符串表示的非负整数 num1 和 num2，返回它们的乘积。
    注意：不能使用 BigInteger 库，也不能直接转成 int。

    示例：
    - num1 = "123", num2 = "456" -> "56088"
    - num1 = "0", num2 = "999" -> "0"

    提示与技巧：
    1. 结果数组大小预设为 num1.size() + num2.size()。
    2. 嵌套循环计算 num1[i] * num2[j]。
    3. 最后处理前导零（注意结果本身为 "0" 的情况）。
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int n1 = num1.size(), n2 = num2.size();
        std::vector<int> res(n1 + n2, 0);
        for (int i = n1-1; i >= 0; i--){
            for (int j = n2-1; j >= 0; j--){
                int multi = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i+j, p2 = i+j+1;

                int sum = multi + res[p2];

                res[p1] += sum / 10;
                res[p2] =  sum % 10;
            }
        }
        string result = "";
        for (int x : res) {
            if (!(result.empty() && x == 0)) {
                result.push_back(x + '0');
            }
        }
        return result.empty() ? "0" : result;
    }
};

class Solution2 {
public:
    string multiply(string num1, string num2) {
        // --- 核心思想：多项式乘法 (卷积) ---
        // 123 * 456 可以看作 (1x^2 + 2x + 3) * (4x^2 + 5x + 6)
        // 我们先计算每一项的系数，最后再统一处理 x=10 时的进位。

        // 特判：如果其中一个是 "0"，直接返回 "0"
        // 否则后续 n+m-1 计算可能出现负数索引
        if (num1 == "0" || num2 == "0") return "0";

        string ret;
        int n = num1.size(), m = num2.size();
        
        // tmp 数组用来存储“不带进位”的中间乘积结果
        // 长度为 n+m-1 是因为最大位数为 (n-1) + (m-1)
        // 注意：在标准 C++ 中建议使用 vector<int> tmp(n + m, 0) 以避免栈溢出
        int tmp[n + m]; 
        
        // 反转字符串：为了让下标 0 对应个位（10^0），下标 1 对应十位（10^1）
        // 这样 num1[i] * num2[j] 的结果直接累加到 tmp[i+j] 即可，逻辑非常清晰
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        // 初始化数组（如果使用 vector 则可跳过此步）
        for(int i = 0; i < n + m; i++) tmp[i] = 0;

        // --- 第一阶段：无进位相乘 ---
        // 嵌套循环计算所有位的乘积组合并累加
        // 时间复杂度：O(N * M)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // 关键逻辑：i位 和 j位 相乘，结果贡献给第 i+j 位
                tmp[i + j] += (num1[i] - '0') * (num2[j] - '0');
            }
        }

        // --- 第二阶段：统一处理进位 ---
        int cur = 0; // 当前处理到的 tmp 下标
        int t = 0;   // 累加器（包含当前位的数值和低位传来的进位）
        
        // 只要 tmp 还没遍历完，或者还有余留的进位 t，就继续处理
        while(cur < n + m - 1 || t != 0) {
            if(cur < n + m - 1) {
                t += tmp[cur++]; // 把当前位的“巨额”数值加入累加器
            }
            ret += (t % 10) + '0'; // 取个位数作为当前位的最终字符
            t /= 10;               // 剩下的全部作为进位传给下一位
        }

        // --- 第三阶段：后续清理 ---
        // 此时 ret 里的顺序是个位在前，需要处理可能存在的前导 0
        //（虽然在卷积法中，如果有特判，只有 "0"*"0" 会触发这个）
        while(ret.size() > 1 && ret.back() == '0') {
            ret.pop_back();
        }
        
        // 最后将结果反转回正常的“高位在前”顺序
        reverse(ret.begin(), ret.end());
        
        return ret;
    }
};

int main() {
    Solution sol;

    // 测试场景描述
    string s1 = "Small numbers";
    string s2 = "Multiply by zero";
    string s3 = "Large numbers (exceeding long long)";
    string s4 = "Both are 10";
    string s5 = "Maximum length carry test";

    vector<string> sn = {s1, s2, s3, s4, s5};

    // 测试用例数据
    struct TestCase {
        string n1;
        string n2;
        string expected;
    };

    vector<TestCase> test_data = {
        {"2", "3", "6"},
        {"123", "0", "0"},
        {"123456789", "987654321", "121932631112635269"},
        {"10", "10", "100"},
        {"999", "999", "998001"}};

    cout << "========== String Multiply 测试 ==========" << endl;

    for (int i = 0; i < test_data.size(); ++i) {
        string n1 = test_data[i].n1;
        string n2 = test_data[i].n2;
        string expected = test_data[i].expected;

        string result = sol.multiply(n1, n2);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    \"" << n1 << "\" * \"" << n2 << "\"" << endl;
        cout << "  Result:   \"" << result << "\"" << endl;
        cout << "  Expected: \"" << expected << "\"" << endl;
        cout << "  Status:   " << (result == expected ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}