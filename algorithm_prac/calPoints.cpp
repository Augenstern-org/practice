#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <sstream>

using namespace std;

class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int> final_points;
        static constexpr string pDC = "+DC";
        for (auto s : operations){
            switch(s[0]){
                case pDC[0]:
                    final_points.push_back(final_points[])
            }
        }
        return 0; 
    }
};

int main() {
    Solution solution;

    // 定义 5 个测试用例
    vector<string> s1 = {"5", "2", "C", "D", "+"};
    vector<string> s2 = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    vector<string> s3 = {"1"};
    vector<string> s4 = {"10", "20", "30", "+", "D", "C"}; 
    vector<string> s5 = {"-10", "D", "D", "C", "+"};

    vector<vector<string>> test_suite = {s1, s2, s3, s4, s5};
    vector<int> expected_results = {30, 27, 1, 120, -30}; // 对应的预期结果

    cout << "========== 棒球比赛计分测试 ==========" << endl;

    for (int i = 0; i < test_suite.size(); ++i) {
        vector<string>& ops = test_suite[i];
        int result = solution.calPoints(ops);

        // 打印输入内容
        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Operations: [ ";
        for (const string& s : ops) cout << "\"" << s << "\" ";
        cout << "]" << endl;

        // 打印结果对比
        cout << "  Result:   " << result << endl;
        cout << "  Expected: " << expected_results[i] << endl;
        cout << (result == expected_results[i] ? "  Status:   PASS" : "  Status:   FAIL") << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}