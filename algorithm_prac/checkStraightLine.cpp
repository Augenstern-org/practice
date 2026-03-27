// Created by Neuroil on 2026/03/27
/*
    题目简述：缀点成线
    给定一个数组 coordinates，其中 coordinates[i] = [x, y] 表示坐标系中的点。
    判断这些点是否全部在同一条直线上。

    示例：
    - [[1,2],[2,3],[3,4]] -> true (斜率均为 1)
    - [[1,1],[2,2],[3,4]] -> false

    提示与进阶要求：
    1. 2 <= coordinates.length <= 1000
    2. -10^4 <= x, y <= 10^4
    3. 思考：如何不用浮点数（避免除法）来比较斜率？
    4. 思考：如果只有两个点，结果必然是什么？
*/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    bool checkStraightLine(vector<vector<int>> &coordinates) {
        int x0 = coordinates[0][0], y0 = coordinates[0][1];
        int x1 = coordinates[1][0], y1 = coordinates[1][1];

        int dx = x1 - x0;
        int dy = y1 - y0;

        for (int i = 2; i < coordinates.size(); ++i) {
            int xi = coordinates[i][0], yi = coordinates[i][1];
            if ((long long)dy * (xi - x0) != (long long)(yi - y0) * dx) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution sol;

    // 测试场景描述
    string s1 = "Basic positive slope";
    string s2 = "Not on a line";
    string s3 = "Horizontal line";
    string s4 = "Vertical line";
    string s5 = "Only two points";

    vector<string> sn = {s1, s2, s3, s4, s5};

    // 测试用例数据
    struct TestCase {
        vector<vector<int>> coords;
        bool expected;
    };

    vector<TestCase> test_data = {
        {{{1, 2}, {2, 3}, {3, 4}, {4, 5}}, true},
        {{{1, 1}, {2, 2}, {3, 4}, {4, 5}}, false},
        {{{1, 2}, {3, 2}, {5, 2}}, true}, // 水平线
        {{{2, 1}, {2, 3}, {2, 5}}, true}, // 垂直线
        {{{1, 1}, {10, 10}}, true}        // 两点必成线
    };

    cout << "========== Check Straight Line 测试 ==========" << endl;

    for (int i = 0; i < test_data.size(); ++i) {
        vector<vector<int>> coords = test_data[i].coords;
        bool expected = test_data[i].expected;

        bool result = sol.checkStraightLine(coords);

        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:    [ ";
        for (const auto &p : coords)
            cout << "[" << p[0] << "," << p[1] << "] ";
        cout << "]" << endl;

        cout << "  Result:   " << (result ? "true" : "false") << endl;
        cout << "  Expected: " << (expected ? "true" : "false") << endl;
        cout << "  Status:   " << (result == expected ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}