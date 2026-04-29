#include <iomanip> // 用于对齐输出
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    /*
                    -0---1---2---3---4---max_col->
            0       [ ] [ ] [ ] [ ] [ ] [ ]
            1       [ ] [ ] [ ] [ ] [ ] [ ]
            2       [ ] [ ] [ ] [ ] [ ] [ ]
            3       [ ] [ ] [ ] [ ] [ ] [ ]
            4       [ ] [ ] [ ] [ ] [ ] [ ]
        max_row     [ ] [ ] [ ] [ ] [ ] [ ]

        max_row == max_col ==> max_bounder
    */
    vector<vector<int>> generateMatrix(int n) {
        if (n == 1) return {{1}};
        // 采用闭区间简化思考
        int max_row = n - 1;
        int min_row = 0;
        int max_col = n - 1;
        int min_col = 0;
        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        int fill_count = 1;
        int row = 0, col = 0;
        for (size_t bounder_index = 0; fill_count <= n * n + 1;
             ++bounder_index) {
            switch (bounder_index & 3) {
            case 0:
                for (; col <= max_row; ++col) { // 向右走
                    result[row][col] = fill_count;
                }
                // 重新定位到正确的起始位置
            default:
                break;
            }
        }
        return {};
    }
};

void printMatrix(const vector<vector<int>> &matrix) {
    if (matrix.empty()) return;
    for (const auto &row : matrix) {
        for (int val : row) {
            cout << setw(4) << val; // 格式化输出，让矩阵对齐
        }
        cout << endl;
    }
}

int main() {
    Solution solution;

    // 测试用例 n1 到 n5
    vector<int> test_cases = {1, 2, 3, 4, 5};

    for (int i = 0; i < test_cases.size(); ++i) {
        int n = test_cases[i];
        cout << "Test Case " << (i + 1) << " (n = " << n << "):" << endl;

        vector<vector<int>> result = solution.generateMatrix(n);

        if (result.empty() || result.size() != n) {
            cout << "  [Result is empty or incorrect size]" << endl;
        } else {
            printMatrix(result);
        }
        cout << "-----------------------------" << endl;
    }

    return 0;
}