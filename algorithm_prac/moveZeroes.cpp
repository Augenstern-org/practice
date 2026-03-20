#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> n1{0, 1, 2, 3, 4, 0, 4, 2, 1};
vector<int> n2{0, 1, 0, 3, 12};
vector<int> n3{8, 99, 103, 0, 10, 1};

vector<vector<int>> test{n1, n2, n3};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int check = 0;
        for (auto n : nums){
            if(n == 0) ++check;
        }
        if (check == nums.size()) return;
        auto fir = nums.begin();
        auto sec = fir + 1;
        int d = 1;
        for (int offset = 0; offset != nums.size(); ++offset){
            if (*fir == 0){
                while (sec != nums.end()-1 && *sec == 0){ 
                    ++sec;
                    ++d;
                }
                *fir = *sec;
                *sec = 0;
            }
            ++fir;
            if (sec != nums.end()-1){
               ++sec;
            }
        }
    }
};

class Solution2 {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        // 第一次遍历：将所有非零元素按顺序移到数组前端
        for (int fast = 0; fast < nums.size(); ++fast) {
            if (nums[fast] != 0) {
                nums[slow] = nums[fast];
                // 如果快慢指针不在同一位置，说明中间有0，当前快指针位置可以置为0
                // 或者等遍历完后，将 slow 之后的位置统一补零
                if (slow != fast) {
                    nums[fast] = 0;
                }
                slow++;
            }
        }
    }
};

int main(){
    Solution2 s;
    for(auto t : test){
        cout << "Result: ";
        for (auto n : t){
            cout << n << " ";
        }
        cout << endl;

        s.moveZeroes(t);

        cout << "Result: ";
        for (auto n : t){
            cout << n << " ";
        }
        cout << endl;
    }
}


