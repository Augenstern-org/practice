#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int sum = 0;
        int ms = mat.size();
        for (int i = 0; i != ms; ++i){
            sum += mat[i][i];
            sum += mat[i][ms-1-i];
        }
        if (ms & 1 != 0){
            sum -= mat[(ms-1)/2][(ms-1)/2];
        }
        return sum;
    }
};

int main() {
    Solution solution;

    // 定义 5 个测试用例：sn
    // s1: 3x3 奇数阶 (有中心重叠)
    vector<vector<int>> s1 = {{1, 2, 3}, 
                              {4, 5, 6}, 
                              {7, 8, 9}}; 
    
    // s2: 4x4 偶数阶 (无中心重叠)
    vector<vector<int>> s2 = {{1, 1, 1, 1}, 
                              {1, 1, 1, 1}, 
                              {1, 1, 1, 1}, 
                              {1, 1, 1, 1}};

    // s3: 1x1 边界情况
    vector<vector<int>> s3 = {{5}};

    // s4: 2x2 偶数阶
    vector<vector<int>> s4 = {{1, 2}, 
                              {3, 4}};

    // s5: 3x3 带有负数
    vector<vector<int>> s5 = {{1, 1, 1}, 
                              {1, 1, 1}, 
                              {1, 1, 1}};

    vector<vector<vector<int>>> test_suite = {s1, s2, s3, s4, s5};
    vector<int> expected = {25, 8, 5, 10, 5};

    cout << "========== 矩阵对角线元素和测试 ==========" << endl;

    for (int i = 0; i < test_suite.size(); ++i) {
        int result = solution.diagonalSum(test_suite[i]);

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Matrix Size: " << test_suite[i].size() << "x" << test_suite[i].size() << endl;
        cout << "  Result:      " << result << endl;
        cout << "  Expected:    " << expected[i] << endl;
        cout << (result == expected[i] ? "  Status:      PASS" : "  Status:      FAIL") << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}