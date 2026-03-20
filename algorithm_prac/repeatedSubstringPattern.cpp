#include <iostream>
#include <string>
#include <vector>

using namespace std;

string s1 = "abab";                                     // 1
string s2 = "aba";                                      // 0
string s3 = "abcabcabcabc";                             // 1
string s4 = "qwertyuiopqwertyuiopqwertyuiop";           // 1
string s5 = "qwertyuioplkjhgfdsaqwertyuioplkjhgfds";    // 0

vector<string> test{s1, s2, s3, s4, s5};

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int s_len = s.size();
        for (int i = 1; i*2 <= s_len; ++i){
            if (s_len % i == 0){
                bool is_match = 1;
                for (int j = i; j != s_len; ++j){
                    if (s[j] != s[j-i]){
                        is_match = 0;
                        break;
                    }
                }
                if (is_match){
                    return true;
                }
            }
        }
        return false;
    }
};

int main(){
    Solution s;
    for(auto t : test){
        cout << "Result: " << s.repeatedSubstringPattern(t) << endl;
    }
}