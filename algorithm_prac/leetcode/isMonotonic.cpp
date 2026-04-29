#include <iostream>
#include <vector>

using namespace std;

// test vectors (only modify these and main)
vector<int> t1{1, 2, 2, 3};       // monotonic increasing -> true
vector<int> t2{6, 5, 4, 4};       // monotonic decreasing -> true
vector<int> t3{1, 3, 2};          // not monotonic -> false
vector<int> t4{1};                // single element -> true
vector<int> t5{2, 2, 2, 1, 4, 5}; // not monotonic -> false

// test
vector<vector<int>> test{t1, t2, t3, t4, t5};

class Solution {
  public:
    bool isMonotonic(vector<int> &nums) {
        if (nums.size() == 0) return false;
        if (nums.size() == 1 || nums.size() == 2) return true;
        int j = 0;
        for (int i = 0; i != nums.size() - 1; ++i) {
            if (nums[i + 1] - nums[i] != 0) j = nums[i + 1] - nums[i];
        }
        if (j == 0) return true;
        if (j > 0) {
            for (int i = 0; i != nums.size() - 1; ++i) {
                if (nums[i + 1] - nums[i] < 0) return false;
            }
        } else if (j < 0) {
            for (int i = 0; i != nums.size() - 1; ++i) {
                if (nums[i + 1] - nums[i] > 0) return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    int idx = 1;
    for (auto &nums : test) {
        cout << "Test " << idx << ": nums = [";
        for (size_t i = 0; i < nums.size(); ++i) {
            cout << nums[i];
            if (i + 1 < nums.size()) cout << ", ";
        }
        bool res = s.isMonotonic(nums);
        cout << "]\n-> isMonotonic = " << (res ? "true" : "false") << endl;
        ++idx;
    }
    return 0;
}

/*
题目考查点：判断数组是否为单调（单调非增或单调非减）。
最优算法：单次线性扫描，维护两个布尔标志 nondec（非减）和 noninc（非增），遇到违背任一性质时更新标志并可早退，时间 O(n)，空间 O(1)。
时间复杂度：O(n)。空间复杂度：O(1)。
实现可优化点：
 - 当前实现通过差值寻找首个非零差再分两次扫描，逻辑复杂且对空数组处理与差值可能存在整数溢出风险（差值相减可能超出 int 边界）；建议改为直接比较大小并在单次循环中维护两个标志。
 - 空数组一般可视为单调（可根据题目定义），建议返回 true 而不是 false。
 - 使用 size_t 与下标时注意类型匹配，避免隐式转换警告。
学习方向：分支预测与分支友好写法（减少分支以提升性能）、单次遍历的早退策略、边界条件处理。
*/