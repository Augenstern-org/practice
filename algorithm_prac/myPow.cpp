// Created by Neuroil on 2026/03/28
/*
    题目简述：实现 pow(x, n)
    计算 x 的 n 次幂。其中 n 是整数。

    示例：
    - x = 2.0, n = 10 -> 1024.0
    - x = 2.0, n = -2 -> 0.25 (即 1/2^2)

    提示与技巧：
    1. 使用快速幂算法 (Binary Exponentiation)。
    2. 注意 n = -2147483648 时取反会溢出，用 long long 接收 n。
    3. 逻辑：如果 n 是偶数，x^n = (x*x)^(n/2)；如果 n 是奇数，x^n = x * (x*x)^(n/2)。
*/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        // 使用 long long 防止 n 取反溢出
        long long N = n;
        // 处理负数幂：x^-n = (1/x)^n
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double res = 1.0;
        double current_product = x; // 记录当前的底数贡献（x^1, x^2, x^4...）

        while (N > 0) {
            // 如果 N 的二进制最后一位是 1，说明这一位需要乘进结果里
            if (N & 1) {
                res *= current_product;
            }
            // 底数翻倍（由于是二进制，每一位代表的权重是前一位的平方）
            current_product *= current_product;
            // 指数右移一位，相当于 N /= 2
            N >>= 1;
        }
        return res;
    }
};

int main() {
    Solution sol;

    struct TestCase {
        double x;
        int n;
        double expected;
    };

    vector<TestCase> test_data = {
        {2.00000, 10, 1024.00000},
        {2.10000, 3, 9.26100},
        {2.00000, -2, 0.25000},
        {1.00000, 2147483647, 1.00000},
        {2.00000, -2147483648, 0.00000} // 极限边界情况
    };

    cout << "========== myPow 测试 ==========" << endl;
    cout << fixed << setprecision(5);

    for (int i = 0; i < test_data.size(); ++i) {
        double x = test_data[i].x;
        int n = test_data[i].n;
        double expected = test_data[i].expected;
        
        double result = sol.myPow(x, n);

        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "  Input:    x = " << x << ", n = " << n << endl;
        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected << endl;
        // 浮点数比较通常允许极小误差
        bool pass = abs(result - expected) < 1e-9;
        cout << "  Status:   " << (pass ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}