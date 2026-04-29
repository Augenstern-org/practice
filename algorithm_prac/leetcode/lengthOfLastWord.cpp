#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int lengthOfLastWord(std::string s) {
        auto fast = s.begin() + 1;
        auto slow = s.begin();
        std::vector<std::string> words;
        // get words
        for (;;++fast){
            if (*fast == ' ' && *slow != ' '){
                std::string a(slow, fast - 1);
                words.push_back(a);
                slow = fast;
            }
            if (*fast != ' ' && *slow == ' '){
                slow = fast;
            }
            if (fast == s.end() && *slow != ' '){
                std::string a(slow, fast - 1);
                words.push_back(a);
                break;
            }
        }
        return words[words.size()-1].size();
    }
};

class Solution2 {
public:
    int lengthOfLastWord(std::string s) {
        int n = static_cast<int>(s.size());
        int i = n - 1;
        while (i >= 0 && s[i] == ' ') --i;
        int len = 0;
        while (i >= 0 && s[i] != ' ') { ++len; --i; }
        return len;
    }
};



int main() {
    // 测试用例（命名为 s1, s2, ...）
    std::string s1 = "Hello World";
    std::string s2 = "   fly me   to   the moon  ";
    std::string s3 = "luffy is still joyboy";
    std::string s4 = "a";
    std::string s5 = "day";

    std::vector<std::string> test{s1, s2, s3, s4, s5};

    Solution2 sol;
    std::cout << "Length Of Last Word Tests:\n";
    for (size_t i = 0; i < test.size(); ++i) {
        const std::string &s = test[i];
        int result = sol.lengthOfLastWord(s);
        std::cout << "Test " << (i + 1) << ": input = " << s
                  << "\n\t-> output = " << result << std::endl;
    }

    return 0;
}

/* 
原实现存在的问题：
- 越界解引用：代码在检查迭代器是否到达 end() 之前就使用了 *fast 和 *slow，
    会导致未定义行为。
- 错误的子串边界：使用 std::string(slow, fast - 1) 生成子串，结束迭代器使用错误，
    可能截断或丢失字符。
- 不安全的初始化：使用 s.begin() + 1 在空串或长度为1时会越界。
- 额外内存与复杂性：原实现构建了一个 vector<string> 存储所有单词，
    既浪费空间也使逻辑冗长易错。

修正方案的优势：
- 简洁且安全：从字符串末尾向前扫描，先跳过尾部空格，再计数字母直到遇到空格或字符串起始，
    避免迭代器算术和多处分支。
- 更高效：单次反向扫描，时间复杂度 O(n)，额外空间 O(1)。
- 可维护性强：逻辑直观，边界情况（仅一个字符、尾部多空格等）自然覆盖。

思路与如何排除冗余信息：
- 思路：题目只需最后一个单词的长度，因此直接从后向前查找最直接、最少操作。
- 排除冗余：不再解析或存储所有单词（去掉 vector<string> 与子串构造），只做必要的两步：
    跳过尾空格、计数最后单词长度，从而减少分支和内存分配点，降低错误面。
*/