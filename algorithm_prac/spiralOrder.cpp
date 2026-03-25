#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    /*
        边界条件梳理：
        将打印逻辑看作贪吃蛇，它沿着边界前进，撞墙前最后一刻转向，四周都是墙时停下。
            分别管理四条边界，利用不断递增的bounder_index切换目前边界。
            当前前进方向的索引值i==bounders[bounder_index&3]时判定为已撞墙。
            转向后下一刻前进方向的索引值j==bounders[bounder_index&3]-1则判定为结束。
            前进一格执行一次result.push_back()

        前进方向：

            matrix[row][col]

            bounder_index & 3 == 0 -> max_col   ==>     [ ][+]
            bounder_index & 3 == 1 -> max_row   ==>     [+][ ]
            bounder_index & 3 == 2 -> min_col   ==>     [ ][-]
            bounder_index & 3 == 3 -> min_row   ==>     [-][ ]
    */
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty()) return {};
        int max_row = matrix.size();
        int max_col = matrix[0].size();
        int min_row = -1, min_col = -1;
        // std::vector<int> direction{1,2,3,0};
        std::vector<int> result;
        int row = 0;
        int col = 0;
        bool flag = 1;
        for (size_t bounder_index = 0;; ++bounder_index) {
            switch (bounder_index & 3) {
            case 0:
                for (; col != max_col; ++col) {
                    result.push_back(matrix[row][col]);
                }
                --col;
                --max_col;
                ++row;
                if (row + 1 == max_row) flag = 0;
                break;
            case 1:
                for (; row != max_row; ++row) {
                    result.push_back(matrix[row][col]);
                }
                --row;
                --max_row;
                --col;
                if (col - 1 == min_col) flag = 0;
                break;
            case 2:
                for (; col != min_col; --col) {
                    result.push_back(matrix[row][col]);
                }
                ++col;
                ++min_col;
                --row;
                if (row - 1 == min_row) flag = 0;
                break;
            case 3:
                for (; row != min_row; --row) {
                    result.push_back(matrix[row][col]);
                }
                ++row;
                ++min_row;
                ++col;
                if (col + 1 == max_col) flag = 0;
                break;
            default:
                break;
            }
            if (!flag) break;
        }
        return result;
    }
};

class Solution2 {
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty()) return {};

        // 1. 初始化边界（使用闭区间更容易思考）
        int min_row = 0, max_row = matrix.size() - 1;
        int min_col = 0, max_col = matrix[0].size() - 1;

        vector<int> result;
        int row = 0, col = 0;

        // 总共需要走的步数
        int total = matrix.size() * matrix[0].size();

        for (int bounder_index = 0; result.size() < total; ++bounder_index) {
            switch (bounder_index & 3) {
            case 0: // 向右走
                for (; col <= max_col; ++col)
                    result.push_back(matrix[row][col]);
                // 修正坐标：col 回到最后一列，row 下移一行，准备向下走
                --col;
                ++row;
                ++min_row; // 上边界下移
                break;
            case 1: // 向下走
                for (; row <= max_row; ++row)
                    result.push_back(matrix[row][col]);
                --row;
                --col;     // 修正坐标：row 回到最后一行，col 左移一列
                --max_col; // 右边界左移
                break;
            case 2: // 向左走
                for (; col >= min_col; --col)
                    result.push_back(matrix[row][col]);
                ++col;
                --row;     // 修正坐标：col 回到第一列，row 上移一行
                --max_row; // 下边界上移
                break;
            case 3: // 向上走
                for (; row >= min_row; --row)
                    result.push_back(matrix[row][col]);
                ++row;
                ++col;     // 修正坐标：row 回到第一行，col 右移一列
                ++min_col; // 左边界右移
                break;
            }
        }
        return result;
    }
};

class Solution3 {
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty()) return {};

        int u = 0, d = matrix.size() - 1;
        int l = 0, r = matrix[0].size() - 1;
        vector<int> result;

        while (true) {
            // 1. 向右走：行不变，列从 l 到 r
            for (int i = l; i <= r; ++i)
                result.push_back(matrix[u][i]);
            if (++u > d) break; // 上边界下移，如果超过下边界则结束

            // 2. 向下走：列不变，行从 u 到 d
            for (int i = u; i <= d; ++i)
                result.push_back(matrix[i][r]);
            if (--r < l) break; // 右边界左移

            // 3. 向左走：行不变，列从 r 到 l
            for (int i = r; i >= l; --i)
                result.push_back(matrix[d][i]);
            if (--d < u) break; // 下边界上移

            // 4. 向上走：列不变，行从 d 到 u
            for (int i = d; i >= u; --i)
                result.push_back(matrix[i][l]);
            if (++l > r) break; // 左边界右移
        }
        return result;
    }
};

// 辅助函数：打印 vector<int>
void printVector(const vector<int> &v) {
    cout << "[";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << (i == v.size() - 1 ? "" : ",");
    }
    cout << "]";
}

int main() {
    Solution2 solution;

    // 定义 5 个测试用例：sn
    // s1: 3x3 标准正方形
    vector<vector<int>> s1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // s2: 3x4 长方形
    vector<vector<int>> s2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    // s3: 单行矩阵
    vector<vector<int>> s3 = {{1, 2, 3, 4, 5}};

    // s4: 单列矩阵
    vector<vector<int>> s4 = {{1}, {2}, {3}};

    // s5: 2x2 小方块
    vector<vector<int>> s5 = {{1, 2}, {3, 4}};

    vector<vector<vector<int>>> test_suite = {s1, s2, s3, s4, s5};

    // 预期结果
    vector<vector<int>> expected = {{1, 2, 3, 6, 9, 8, 7, 4, 5},
                                    {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7},
                                    {1, 2, 3, 4, 5},
                                    {1, 2, 3},
                                    {1, 2, 4, 3}};

    cout << "========== 螺旋矩阵遍历测试 ==========" << endl;

    for (int i = 0; i < test_suite.size(); ++i) {
        vector<int> result = solution.spiralOrder(test_suite[i]);

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Input Matrix Size: " << test_suite[i].size() << "x"
             << test_suite[i][0].size() << endl;
        cout << "  Result:   ";
        printVector(result);
        cout << endl;
        cout << "  Expected: ";
        printVector(expected[i]);
        cout << endl;

        bool is_pass = (result == expected[i]);
        cout << (is_pass ? "  Status:   PASS" : "  Status:   FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}