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
            check += n;
        }
        if (check == 0) return;
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

int main(){
    Solution s;
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


