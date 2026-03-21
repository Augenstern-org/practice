#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> t1{3, 5, 1};
vector<int> t2{1, 2, 4};
vector<int> t3{7, 7, 7};
vector<int> t4{1, 2, 4};
vector<int> t5{1, 3, 3, 5};

vector<vector<int>> test{t1, t2, t3, t4, t5};

class Solution {
  public:
    bool canMakeArithmeticProgression(vector<int> &arr) {
        if (arr.size() <= 2) return true;
        sort(arr.begin(), arr.end());
        int d = arr[1] - arr[0];
        for (size_t i = 2; i < arr.size(); ++i) {
            if (arr[i] - arr[i - 1] != d) return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    int idx = 1;
    for (auto nums : test) {
        cout << "Test " << idx << ": nums = [";
        for (size_t i = 0; i < nums.size(); ++i) {
            cout << nums[i];
            if (i + 1 < nums.size())
                cout << ", ";
        }
        bool res = s.canMakeArithmeticProgression(nums);
        cout << "] -> canMakeArithmeticProgression = "
             << (res ? "true" : "false") << endl;
        ++idx;
    }
    return 0;
}

/*
题目考查点：判断数组是否能通过重新排列后构成等差数列（要求判断是否存在一种排列使相邻差相同）。
最优算法：常见且简洁的方法是先排序（O(n log n)），然后线性检查相邻差是否一致，时间 O(n log n)，空间 O(1)（就地排序）。
另一种在特殊条件下可达到 O(n) 的方法需要借助哈希表与差值判断，但实现更复杂且常数开销更大。
时间复杂度：排序法 O(n log n)。空间复杂度：取决于排序实现（std::sort 额外栈 O(log n)）。
实现可优化点：
 - 当前实现已采用排序并校验，是标准且高效的做法；注意传参是否需要 const 引用以避免不必要拷贝。
 - 对于非常大的输入，考虑按需使用稳定性更高或并行排序，但题目通常不需要。
学习方向：排序后检查常见题型、如何在不排序的情况下判断等差可能性（哈希与数学推导）、复杂度权衡。
*/