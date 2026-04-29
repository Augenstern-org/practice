#include <numeric> // 用于 std::max
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    int maximumWealth(vector<vector<int>> &accounts) {
        int max = 0;
        for (int i = 0; i != accounts.size(); ++i) {
            int sum = 0;
            for (auto &w : accounts[i]) {
                sum += w;
            }
            if (max < sum) max = sum;
        }
        return max;
    }
};

class Solution2 {
public:
    int maximumWealth(vector<vector<int>>& accounts) { 
        int maxWealth = 0;
        for (const auto& customer : accounts) {
            int currentWealth = 0;
            for (int bank : customer) {
                currentWealth += bank;
            }
            if (currentWealth > maxWealth) {
                maxWealth = currentWealth;
            }
        }
        return maxWealth;
    }
};

class Solution3 {
  public:
    int maximumWealth(vector<vector<int>> &accounts) {
        int max = 0;
        for (auto& c : accounts) {
        max = std::max(max, std::accumulate(c.begin(), c.end(), 0));
        }
        return max;
    }
};

int main() {
    Solution solution;

    // 定义 5 个测试用例：sn
    vector<vector<int>> s1 = {{1, 2, 3}, {3, 2, 1}};            // 预期: 6
    vector<vector<int>> s2 = {{1, 5}, {7, 3}, {3, 5}};          // 预期: 10
    vector<vector<int>> s3 = {{2, 8, 7}, {7, 1, 3}, {1, 9, 5}}; // 预期: 17
    vector<vector<int>> s4 = {{10}}; // 预期: 10 (只有一个客户一家银行)
    vector<vector<int>> s5 = {
        {1, 1, 1}, {1, 1, 1}, {1, 1, 1}}; // 预期: 3 (所有客户资产相同)

    vector<vector<vector<int>>> test_suite = {s1, s2, s3, s4, s5};
    vector<int> expected = {6, 10, 17, 10, 3};

    cout << "========== 最富有客户资产总量测试 ==========" << endl;

    for (int i = 0; i < test_suite.size(); ++i) {
        int result = solution.maximumWealth(test_suite[i]);

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Accounts: [ ";
        for (const auto &row : test_suite[i]) {
            cout << "[";
            for (int j = 0; j < row.size(); ++j) {
                cout << row[j] << (j == row.size() - 1 ? "" : ",");
            }
            cout << "] ";
        }
        cout << "]" << endl;

        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected[i] << endl;
        cout << (result == expected[i] ? "  Status:   PASS"
                                       : "  Status:   FAIL")
             << endl;
        cout << "------------------------------------------" << endl;
    }

    return 0;
}