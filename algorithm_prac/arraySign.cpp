#include <iostream>
#include <vector>

using namespace std;

vector<int> t1{-1, 4, -7, 2, 5, -8, 3, 0, -3, 2};
vector<int> t2{-1, 6, -3, 3, -9, 1, -7, 9};
vector<int> t3{1, -4, -6, 3};
vector<int> t4{0, 1};
vector<int> t5{9, 2, -7};

vector<vector<int>> test{t1, t2, t3, t4, t5};

class Solution {
  public:
    int arraySign(vector<int> &nums) {
        int sgn = 1;
        for (auto n : nums) {
            if (n == 0) {
                return 0;
            }
            if (n < 0) {
                sgn = -sgn;
            }
        }
        return sgn;
    }
};

int main() {
    Solution s;
    int idx = 1;
    for (auto &nums : test) {
        cout << "Test " << idx << ": nums = [";
        for (size_t i = 0; i < nums.size(); ++i) {
            cout << nums[i];
            if (i + 1 < nums.size())
                cout << ", ";
        }
        cout << "]\n-> sign = " << s.arraySign(const_cast<vector<int> &>(nums))
             << std::endl;
        ++idx;
    }
    return 0;
}

/*
题目考查点：判断数组中所有元素的乘积的符号（正/负/零），考察符号判定与溢出规避。
最优算法：一次遍历：若遇到 0 返回 0；否则统计负数个数，奇数个负数返回 -1，偶数返回 1。时间 O(n)，空间 O(1)。
时间复杂度：O(n)。空间复杂度：O(1)。
实现可优化点：
 - 当前实现已为最优思想，可考虑函数签名使用 const 引用以避免 const_cast。
 - 对极端大输入保持线性扫描，避免实际乘积计算以免溢出。
学习方向：位运算技巧（偶奇判断）、稳定性（处理边界：空数组的定义）、函数接口设计（const 与引用）。
*/