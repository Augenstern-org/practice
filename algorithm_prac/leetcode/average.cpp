// Created by Neuroil on 2026/03/26
/*
    题目简述：去掉最低工资和最高工资后的平均值
    给定一个整数数组
   salary，其中每个数字唯一。请返回去掉最低和最高工资后，剩余员工的平均工资。

    示例说明：
    - 输入：[4000, 3000, 1000, 2000] -> 去掉 1000 和 4000，平均值 (2000+3000)/2
   = 2500.0
    - 输入：[1000, 2000, 3000] -> 去掉 1000 和 3000，平均值 (2000)/1 = 2000.0

    提示与进阶要求：
    1. 3 <= salary.length <= 100
    2. 10^3 <= salary[i] <= 10^6
    3. 结果与真实值误差在 10^-5 以内均视为正确。
    4. 思考：如何在一次遍历中同时找到最大值、最小值并求和？
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    double average(vector<int> &salary) {
        std::sort(salary.begin(), salary.end());
        double sum = 0.0;
        for (int i = 1; i != salary.size() - 1; ++i) {
            sum += salary[i];
        }
        return sum / (salary.size() - 2);
    }
};

class Solution2 {
  public:
    double average(std::vector<int> &salary) {
        int min = salary[0];
        int max = salary[0];
        double sum = 0.0;
        for (const auto &s : salary) {
            sum += s;
            if (min > s) min = s;
            if (max < s) max = s;
        }
        return (sum - min - max) / (salary.size() - 2);
    }
};

int main() {
    Solution2 sol;

    // 测试场景描述
    string s1 = "Basic Case (4 elements)";
    string s2 = "Minimum length (3 elements)";
    string s3 = "Large values case";
    string s4 = "Values in descending order";
    string s5 = "Values in ascending order";

    vector<string> sn = {s1, s2, s3, s4, s5};

    // 测试用例数据
    struct TestCase {
        vector<int> input;
        double expected;
    };

    vector<TestCase> test_data = {
        {{4000, 3000, 1000, 2000}, 2500.0},
        {{1000, 2000, 3000}, 2000.0},
        {{6000, 5000, 4000, 3000, 2000, 1000}, 3500.0},
        {{9000, 8000, 7000, 6000, 5000}, 7000.0},
        {{10000, 20000, 30000, 40000}, 25000.0}};

    cout << fixed << setprecision(5); // 设置输出精度
    cout << "========== Average Salary 测试 ==========" << endl;

    for (int i = 0; i < test_data.size(); ++i) {
        vector<int> current_input = test_data[i].input;
        double expected = test_data[i].expected;

        // 调用待实现的函数
        double result = sol.average(current_input);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    [ ";
        for (int val : current_input)
            cout << val << " ";
        cout << "]" << endl;

        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected << endl;

        // 简单判断状态（允许微小误差）
        bool pass = abs(result - expected) < 1e-5;
        cout << "  Status:   " << (pass ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}