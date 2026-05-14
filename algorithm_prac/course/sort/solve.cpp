// Created by Neuroil on 2025/01/15

/*
 * 题目：最少教室数 (Minimum Number of Classrooms)
 *
 * 题目描述：
 *   给定一系列会议的开始时间和结束时间，每场会议需要使用一间教室。
 *   同一时间一间教室只能用于一场会议。要求计算安排所有会议所需的最少教室数量。
 *
 * 示例：
 *   输入：meetings = [ [2, 4], [2.5, 3], [4.5, 5], [5, 6] ]
 *   输出：2
 *   解释：
 *     会议A：2:00 ~ 4:00
 *     会议B：2:30 ~ 3:00
 *     会议C：4:30 ~ 5:00
 *     会议D：5:00 ~ 6:00
 *     在 2:30 ~ 3:00 时间段，会议A和会议B同时进行，需要2间教室。
 *     其他时间段最多只有1场会议，因此最少需要2间教室。
 *
 * 提示：
 *   - 输入为若干会议时间区间，每个区间表示为 (start, end)
 *   - 时间以小时为单位（整数或小数均可）
 *   - 结束时间 > 开始时间
 *
 * 进阶要求：
 *   - 尝试使用排序 + 最小堆（优先队列）实现 O(n log n) 的算法
 *   - 也可以尝试扫描线（差分数组）的思想
 *   - 思考当 end == 另一个会议的 start 时是否可以共用教室
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Stack {
    int depth;
    std::vector<int> data;

    Stack() : depth(0), data{} {}
    bool empty() const { return data.empty(); }

    void use() {
        if (data.empty()) {
            ++depth;
            return;
        }
        data.pop_back();
    }

    void free() { data.push_back(1); }
};

class Solution {
  public:
    int solve(vector<pair<double, double>>& meetings) {
        Stack free_room;
        vector<pair<double, int>> events;
        events.reserve(meetings.size() * 2);
 
        for (auto& m : meetings) {
            events.emplace_back(m.first, 1);
            events.emplace_back(m.second, -1);
        }
        sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });

        for (auto& e : events) {
            if (e.second == 1) {
                free_room.use();
            } else {
                free_room.free();
            }
        }
        return free_room.depth;
    }
};

int main() {
    // 测试用例名称向量
    vector<string> sn = {
        "基本示例：四场会议有部分重叠",         "无重叠：所有会议时间互不相交",
        "完全重叠：所有会议在同一时间段内举行", "嵌套重叠：会议时间呈嵌套结构",
        "边界情况：会议时间首尾相接",           "单场会议：只有一个会议"};

    // 测试输入数据（会议时间区间列表）
    vector<vector<pair<double, double>>> testInputs = {
        {{2, 4}, {2.5, 3}, {4.5, 5}, {5, 6}}, // 期望：2
        {{1, 2}, {2, 3}, {3, 4}, {4, 5}},     // 期望：1
        {{1, 5}, {1.5, 4}, {2, 3}, {1, 6}},   // 期望：4
        {{1, 6}, {2, 5}, {3, 4}},             // 期望：3
        {{1, 2}, {2, 3}, {1.5, 2.5}},         // 期望：2
        {{1, 2}}                              // 期望：1
    };

    // 预期结果
    vector<int> expected = {2, 1, 4, 3, 2, 1};

    Solution solution;

    cout << "========== solve 测试 ==========" << endl;

    for (int i = 0; i < (int)sn.size(); i++) {
        cout << "Test Case " << (i + 1) << " (" << sn[i] << "):" << endl;
        cout << "Input:    [";
        for (int j = 0; j < (int)testInputs[i].size(); j++) {
            if (j > 0) cout << ", ";
            cout << "(" << testInputs[i][j].first << ", "
                 << testInputs[i][j].second << ")";
        }
        cout << "]" << endl;

        int result = solution.solve(testInputs[i]);

        cout << "Result:   " << result << endl;
        cout << "Expected: " << expected[i] << endl;
        cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL")
             << endl;
        cout << "------------------------------------" << endl;
    }

    return 0;
}