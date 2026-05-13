// Created by Neuroil on 2026/05/13

/*
 * 题目：图的广度优先搜索 (BFS)
 *
 * 题目要求：
 *   实现一个函数，对给定的图（以邻接表形式表示）进行广度优先搜索，
 *   并返回从指定起始顶点出发的访问顺序。
 *
 * 示例说明：
 *   图：0 -> [1,2,3], 1 -> [0,4], 2 -> [0], 3 -> [0], 4 -> [1]
 *   起始顶点：0
 *   预期输出：[0, 1, 2, 3, 4]
 *
 * 提示：
 *   - 使用 visited 集合避免重复访问
 *   - 使用队列（queue）实现逐层遍历
 *   - 访问邻居时按邻接表中的顺序进行
 *
 * 进阶要求：
 *   - 考虑图不连通的情况（需额外处理所有顶点）
 *   - 考虑使用迭代器和泛型
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

class Solution {
  public:
    std::vector<int> bfs(std::vector<std::vector<int>> graph, int start) {
        // TODO: implement BFS
        std::vector<int> visit{start};
        std::queue<int> q;
        for (auto v : graph[start]) {
            if (visit.end() != std::find(visit.begin(),visit.end(),v)) continue;
            q.push(v);
            visit.push_back(v);
        }
        while (!q.empty()) {
            int curr = q.front();
            for (auto v : graph[curr]) {
                if (visit.end() != std::find(visit.begin(),visit.end(),v)) continue;
                q.push(v);
                visit.push_back(v);
            }
            q.pop();
        }
        std::vector<int> res;
        for(auto v : visit) res.push_back(v);
        return res;
    }
};

int main() {
    // 测试场景名称向量
    std::vector<std::string> sn = {
        "简单连通图 (4个顶点)", "星形图 (中心节点连接所有叶子)",
        "线性图 (链式结构)", "带环图 (存在环的图)", "不连通图 (包含孤立顶点)"};

    // 对应的图（邻接表）和起始顶点
    std::vector<std::vector<std::vector<int>>> graphs = {
        {{1, 2}, {0, 3}, {0}, {1}},         // 简单连通图
        {{1, 2, 3, 4}, {0}, {0}, {0}, {0}}, // 星形图（0为中心）
        {{1}, {0, 2}, {1, 3}, {2}},         // 线性图 0-1-2-3
        {{1, 2}, {0, 3}, {0, 3}, {1, 2}},   // 三角形+额外顶点
        {{1}, {0}, {}, {3}, {}}             // 不连通：0-1, 2孤立, 3-4
    };

    std::vector<int> starts = {0, 0, 0, 0, 0};

    // 预期结果（手动准备）
    std::vector<std::vector<int>> expected = {
        {0, 1, 2, 3}, {0, 1, 2, 3, 4}, {0, 1, 2, 3}, {0, 1, 2, 3}, {0, 1}
        // 注意：不连通时只遍历到一个连通分量
    };

    Solution sol;
    std::cout << "========== bfs_students 测试 ==========" << std::endl;

    for (size_t i = 0; i < sn.size(); ++i) {
        std::cout << "Test Case " << (i + 1) << " (" << sn[i]
                  << "):" << std::endl;
        std::cout << "Input:    graph = [";
        for (size_t u = 0; u < graphs[i].size(); ++u) {
            if (u > 0) std::cout << ", ";
            std::cout << "[";
            for (size_t v = 0; v < graphs[i][u].size(); ++v) {
                if (v > 0) std::cout << ",";
                std::cout << graphs[i][u][v];
            }
            std::cout << "]";
        }
        std::cout << "], start = " << starts[i] << std::endl;

        std::vector<int> result = sol.bfs(graphs[i], starts[i]);

        std::cout << "Result:   [";
        for (size_t j = 0; j < result.size(); ++j) {
            if (j > 0) std::cout << ",";
            std::cout << result[j];
        }
        std::cout << "]" << std::endl;

        std::cout << "Expected: [";
        for (size_t j = 0; j < expected[i].size(); ++j) {
            if (j > 0) std::cout << ",";
            std::cout << expected[i][j];
        }
        std::cout << "]" << std::endl;

        bool pass = (result == expected[i]);
        std::cout << "Status:   " << (pass ? "PASS" : "FAIL") << std::endl;
        if (i < sn.size() - 1)
            std::cout << "------------------------------------" << std::endl;
    }

    return 0;
}