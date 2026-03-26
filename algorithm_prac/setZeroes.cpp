// Created by Neuroil on 2026/03/26
/*
    题目简述：矩阵置零 (Set Matrix Zeroes)
    给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。
    
    进阶要求：
    1. 使用原地算法（In-place）。
    2. 算法 1 (Solution)：使用 O(m + n) 额外空间，利用两个哈希表记录零的位置。
    3. 算法 2 (Solution2)：使用 O(1) 额外空间，利用矩阵的第一行和第一列作为标记位。
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_set>

using namespace std;

// 方法一：哈希集合法 - 空间复杂度 O(m + n)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        unordered_set<int> r_pos, c_pos;

        // 第一遍遍历：记录 0 出现的行与列
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (matrix[r][c] == 0) {
                    r_pos.insert(r);
                    c_pos.insert(c);
                }
            }
        }

        // 第二遍遍历：根据记录置零
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r_pos.count(r) || c_pos.count(c)) {
                    matrix[r][c] = 0;
                }
            }
        }
    }
};

// 方法二：原地标记法 - 空间复杂度 O(1)
class Solution2 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        bool firstRowHasZero = false;
        bool firstColHasZero = false;

        // 1. 检查第一行是否有零
        for (int j = 0; j < cols; ++j) {
            if (matrix[0][j] == 0) {
                firstRowHasZero = true;
                break;
            }
        }

        // 2. 检查第一列是否有零
        for (int i = 0; i < rows; ++i) {
            if (matrix[i][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }

        // 3. 使用第一行和第一列作为“备忘录”
        // 遍历除首行首列外的所有元素，若发现 0，则在对应的首行和首列做标记
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // 标记该行需置零
                    matrix[0][j] = 0; // 标记该列需置零
                }
            }
        }

        // 4. 根据“备忘录”标记，将内部元素置零
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 5. 最后处理第一行和第一列本身
        if (firstRowHasZero) {
            for (int j = 0; j < cols; ++j) matrix[0][j] = 0;
        }
        if (firstColHasZero) {
            for (int i = 0; i < rows; ++i) matrix[i][0] = 0;
        }
    }
};

class Solution3 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool col_0 = false;
        int m = matrix.size();
        int n = matrix[0].size();

        // 1. 先扫描第一列，确定第一列最后是否需要全部置零
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                col_0 = true;
            }
        }

        // 2. 使用第一行和第一列作为标记位
        // 注意：j 从 1 开始，因为第一列的状态由 col_0 维护
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        // 3. 根据内部标记位进行置零（避开首行首列，防止标记被提前覆盖）
        for (int i = 1; i < m ; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 4. 处理第一行的状态（由 matrix[0][0] 决定）
        if (matrix[0][0] == 0) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        // 5. 处理第一列的状态（由 col_0 决定）
        if (col_0) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

// 辅助打印函数
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        cout << "      [ ";
        for (int val : row) cout << setw(2) << val << " ";
        cout << " ]" << endl;
    }
}

int main() {
    Solution2 sol; // 此处可切换 Solution 或 Solution2 进行测试

    string s1 = "Basic 3x3 Case";
    string s2 = "Multi-Zero Case";
    string s3 = "First Row Zero Case";
    string s4 = "Single Element Zero";
    string s5 = "No Zero Case";

    vector<string> sn = {s1, s2, s3, s4, s5};

    vector<vector<vector<int>>> inputs = {
        {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
        {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}},
        {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}},
        {{0}},
        {{1, 2}, {3, 4}}
    };

    vector<vector<vector<int>>> expects = {
        {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}},
        {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}},
        {{0, 0, 0}, {0, 4, 5}, {0, 7, 8}},
        {{0}},
        {{1, 2}, {3, 4}}
    };

    cout << "========== SetZeroes 测试 ==========" << endl;

    for (int i = 0; i < inputs.size(); ++i) {
        vector<vector<int>> matrix = inputs[i];
        cout << "Test Case " << i + 1 << " (" << sn[i] << "):" << endl;
        cout << "  Input:" << endl;
        printMatrix(matrix);

        sol.setZeroes(matrix);

        cout << "  Result:" << endl;
        printMatrix(matrix);

        cout << "  Expected:" << endl;
        printMatrix(expects[i]);

        cout << "  Status:   " << (matrix == expects[i] ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}