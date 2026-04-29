#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    string tictactoe(vector<vector<int>> &moves) {
        std::vector<int> counter(8, 0);
        /*
            0 -> 主对角线
            1 -> 副对角线
            2 -> row_0
            3 -> row_1
            4 -> row_2
            5 -> col_0
            6 -> col_1
            7 -> col_2
        */
        for (int i = 0; i != moves.size(); ++i) {
            int score = (i % 2 == 0) ? 1 : -1;
            if (moves[i][0] == moves[i][1])
                counter[0] += score; // 主
            if (moves[i][0] + moves[i][1] == 2)
                counter[1] += score; // 副

            if (moves[i][0] == 0) { // row_0
                counter[2] += score;
                if (moves[i][1] == 0)
                    counter[5] += score;
                else if (moves[i][1] == 1)
                    counter[6] += score;
                else
                    counter[7] += score;
            } else if (moves[i][0] == 1) {
                counter[3] += score;
                if (moves[i][1] == 0)
                    counter[5] += score;
                else if (moves[i][1] == 1)
                    counter[6] += score;
                else
                    counter[7] += score;
            } else {
                counter[4] += score;
                if (moves[i][1] == 0)
                    counter[5] += score;
                else if (moves[i][1] == 1)
                    counter[6] += score;
                else
                    counter[7] += score;
            }
            for (auto s : counter) {
                if (s == 3) return "A";
                if (s == -3) return "B";
            }
        }
        if (moves.size() == 9) return "Draw";
        return "Pending";
    }
};

class Solution2 {
public:
    string tictactoe(vector<vector<int>>& moves) {
        // 0:主对角线, 1:副对角线, 2-4:行, 5-7:列
        std::vector<int> counter(8, 0);

        for (int i = 0; i < moves.size(); ++i) {
            int r = moves[i][0];
            int c = moves[i][1];
            int score = (i % 2 == 0) ? 1 : -1;

            // 1. 更新行和列 (利用偏移量直接定位索引)
            counter[r + 2] += score;
            counter[c + 5] += score;

            // 2. 更新主对角线 (r == c)
            if (r == c) counter[0] += score;

            // 3. 更新副对角线 (r + c == 2)
            // 注意：这里必须用 if，不能用 else if，因为 (1,1) 两者皆是
            if (r + c == 2) counter[1] += score;

            // 4. 实时检查胜负
            for (int s : counter) {
                if (s == 3) return "A";
                if (s == -3) return "B";
            }
        }

        return (moves.size() == 9) ? "Draw" : "Pending";
    }
};

int main() {
    Solution solution;

    // 1. A 获胜 (示例1)
    vector<vector<int>> s1 = {{0, 0}, {2, 0}, {1, 1}, {2, 1}, {2, 2}};

    // 2. B 获胜 (示例2)
    vector<vector<int>> s2 = {{0, 0}, {1, 1}, {0, 1}, {0, 2}, {1, 0}, {2, 0}};

    // 3. 平局 (示例3)
    vector<vector<int>> s3 = {{0, 0}, {1, 1}, {2, 0}, {1, 0}, {1, 2},
                              {2, 1}, {0, 1}, {0, 2}, {2, 2}};

    // 4. 游戏未结束 (Pending) - 只走了两步
    vector<vector<int>> s4 = {{0, 0}, {1, 1}};

    // 5. A 获胜 (对角线)
    vector<vector<int>> s5 = {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {2, 2}};

    vector<vector<vector<int>>> test_suite = {s1, s2, s3, s4, s5};
    vector<string> expected = {"A", "B", "Draw", "Pending", "A"};

    cout << "========== 井字棋胜负判定测试 ==========" << endl;

    for (int i = 0; i < test_suite.size(); ++i) {
        string result = solution.tictactoe(test_suite[i]);

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Moves: ";
        for (auto &m : test_suite[i])
            cout << "[" << m[0] << "," << m[1] << "] ";
        cout << endl;

        cout << "  Result:   " << (result.empty() ? "EMPTY" : result) << endl;
        cout << "  Expected: " << expected[i] << endl;
        cout << (result == expected[i] ? "  Status:   PASS"
                                       : "  Status:   FAIL")
             << endl;
        cout << "--------------------------------------" << endl;
    }

    return 0;
}