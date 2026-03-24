#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    /*
        简化条件：
        1.每次循环至少旋转90度。因为0度显然代表永不回头
            这意味着最多4次循环，方向便会回到北方
        2.对于位移，如果单次位移v=0，那么显而易见回到原点
            如果v!=0，那么位移会随着方向在四次循环之后变为0

        ==> 因此仅需判断单次循环之后是否具备：
                1.方向归位（这里是朝北）
                2.位移不为0

        实际上就是让机器人永不回头地向前走
    */
    bool isRobotBounded(string instructions) {
        /*
            0   ->  north   =>  ++y
            1   ->  east    =>  ++x
            2   ->  south   =>  --y
            3   ->  west    =>  --x
        */
        unsigned int direction = 0;
        std::vector<int> pos(2, 0);
        for (auto i : instructions) {
            if (i == 'L') {
                direction = (direction + 1) & 3;
            } else if (i == 'R') {
                direction = (direction - 1) & 3;
            } else {
                if (direction == 0)
                    ++pos[1];
                else if (direction == 1)
                    ++pos[0];
                else if (direction == 2)
                    --pos[1];
                else
                    --pos[0];
            }
        }
        if (direction == 0 && (pos[0] != 0 || pos[1] != 0)) return false;
        return true;
    }
};

int main() {
    Solution solution;

    // 定义 5 个测试用例：sn
    string s1 = "GGLLGG"; // 示例 1: 回到原点，有环
    string s2 = "GG";     // 示例 2: 一直向北，无环
    string s3 = "GL";     // 示例 3: 四次循环回到原点，有环
    string s4 = "GLR";    // 抵消旋转后朝北且有位移，无环
    string s5 = "GLLR";   // 最终朝向变化，有环

    vector<string> test_suite = {s1, s2, s3, s4, s5};
    vector<bool> expected = {true, false, true, false, true};

    cout << "========== 机器人困于环中测试 ==========" << endl;

    for (int i = 0; i < test_suite.size(); ++i) {
        string inst = test_suite[i];
        bool result = solution.isRobotBounded(inst);

        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "  Instructions: " << inst << endl;
        cout << "  Result:       " << (result ? "true" : "false") << endl;
        cout << "  Expected:     " << (expected[i] ? "true" : "false") << endl;
        cout << (result == expected[i] ? "  Status:       PASS"
                                       : "  Status:       FAIL")
             << endl;
        cout << "--------------------------------------" << endl;
    }

    return 0;
}