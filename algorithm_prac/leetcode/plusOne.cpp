#include <iostream>
#include <vector>

using namespace std;

vector<int> t1{1,2,3,4,5,6,7,8,9};
vector<int> t2{1,0,4,9,9,3,8};
vector<int> t3{9,9,9,9,9,9};
vector<int> t4{9};
vector<int> t5{1,1,4,5,1,4};

vector<vector<int>> test{t1, t2, t3, t4, t5};

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int d_size = digits.size();
        for (int i = d_size - 1; i >= 0; --i) {
            if (digits[i] < 9) {
                ++digits[i];
                return digits;
            }
            digits[i] = 0;
        }
        vector<int> r_vec(d_size + 1, 0);
        r_vec[0] = 1;
        return r_vec;
    }
};

int main() {
    Solution s;
    int count = 1;
    for (auto &t : test) {
        cout << "result_" << count << ": ";
        vector<int> temp = s.plusOne(t);
        for (size_t i = 0; i < temp.size(); ++i) {
            cout << temp[i] << " ";
        }
        cout << endl;
        ++count;
    }
    return 0;
}

/*
题目考查点：把按位存储的大整数加一，考察进位传播和数组/字符串表示大整数的处理。
最优算法：从低位向高位遍历，遇到小于9的位直接加一并返回，遇到 9 置 0 并继续传播；若最高位仍有进位则在首位插入 1。时间 O(n)，空间 O(1)（除返回新数组外）。
时间复杂度：O(n)，n 为位数；空间复杂度：O(1)（原地修改）或 O(n) 在需要新数组时。
实现可优化点：
 - 处理空向量（目前实现假设非空）；建议先检查 digits.empty()。
 - 使用 size_t/unsigned 与 int 混合时注意类型转换与比较，避免警告。
 - 减少不必要的拷贝（传参可用引用），已有实现已较为简洁。
学习方向：大整数表示法、进位处理模式、边界条件（全 9 序列）以及如何在不溢出的情况下操作大数。
*/