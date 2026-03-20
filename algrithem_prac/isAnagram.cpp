#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;
        int s_size = s.size();
        // 0 -> 已用 | 1 -> 未用
        vector<bool> p(s_size * 2, 1);
        for(int i = 0; i != s_size; ++i){

            cout << "i:p[" << i << "]: " << p[i] << endl;

            p[i] = 0;
            for(int j = 0; j != s_size; ++j){

                cout << "j:p[" << s_size + j << "]: " << p[s_size + j] << endl;

                if (p[s_size + j] == 0){
                    continue;
                }
                if (s[i] == t[j]){
                    p[s_size + j] = 0;
                    break;
                }
            }
        }
        int check = 0;
        for(auto b : p){
            check += b;
            cout << "p:" << b;
        }
        cout << endl;
        if (check == 0) {return true;}
        return false;
    }
};

class Solution2 {
public:
    bool isAnagram(string s, string t) {
        char check = 0;
        for (auto c : s){
            check ^= c;
        }
        for (auto c : t){
            check ^= c;
        }
        if (check == 0){ return true;}
        return false;
    }
};

class SolutionFinal {
public:
    bool isAnagram(string s, string t) {
        vector<int> counter(26, 0);
        for (auto c : s){
            ++counter[c - 'a'];
        }
        for (auto c : t){
            --counter[c - 'a'];
        }
        for (auto c : counter){
            if (c != 0){
                return false;
            }
        }
        return true;
    }
};

int main(){
    SolutionFinal s;
    cout << s.isAnagram("rat", "car") << endl;
    return 0;
}