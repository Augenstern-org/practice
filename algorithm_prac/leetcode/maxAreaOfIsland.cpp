// Created by Neuroil on 2026/05/13

/*
 * 题目：最大岛屿面积（Max Area of Island）
 *
 * 给你一个大小为 m x n 的二进制矩阵 grid。
 * 岛屿是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在
 * 水平或者竖直的四个方向上相邻。你可以假设 grid 的四个边缘都被
 * 0（代表水）包围着。 岛屿的面积是岛上值为 1 的单元格的数目。 计算并返回 grid
 * 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。
 *
 * 示例 1:
 * Input:
 *   grid = [
 *     [0,0,1,0,0,0,0,1,0,0,0,0,0],
 *     [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *     [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *     [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *     [0,1,0,0,1,1,0,0,1,1,1,0,0],
 *     [0,0,0,0,0,0,0,0,0,0,1,0,0],
 *     [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *     [0,0,0,0,0,0,0,1,1,0,0,0,0]
 *   ]
 * Output: 6
 * 解释：最大的岛屿面积为 6（最中间的那个岛屿）。
 *
 * 示例 2:
 * Input: grid = [[0,0,0,0,0,0,0,0]]
 * Output: 0
 *
 * 提示：
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 50
 * - grid[i][j] 为 0 或 1
 */

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Solution {
  public:
    bool inArea(std::vector<std::vector<int>>& grid, int x, int y) {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
            return false;
        return true;
    }

    int dfs(std::vector<std::vector<int>>& grid, int x, int y) {
        if (!inArea(grid, x, y) || grid[x][y] != 1) return 0;
        grid[x][y] = 2;
        return 1 + dfs(grid, x - 1, y)
                 + dfs(grid, x + 1, y)
                 + dfs(grid, x, y - 1)
                 + dfs(grid, x, y + 1);
    }

    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        int max = 0;
        for (int x = 0; x != grid.size(); ++x) {
            for (int y = 0; y != grid[0].size(); ++y) {
                int temp = dfs(grid, x, y);
                max = temp > max ? temp : max;
            }
        }
        return max;
    }
};

int main() {
    // 测试名向量 sn
    const std::vector<std::string> sn = {"示例 1：包含多个岛屿，最大面积为 6",
                               "示例 2：全为 0，无岛屿", "单个土地单元格",
                               "全部为 1 的矩形", "只有一个岛屿呈蛇形分布"};

    // 测试输入和预期结果
    std::vector<std::vector<std::vector<int>>> inputs = {
        {// Test 1
         {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
         {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}},
        {// Test 2
         {0, 0, 0, 0, 0, 0, 0, 0}},
        {// Test 3
         {1}},
        {// Test 4
         {1, 1, 1, 1},
         {1, 1, 1, 1},
         {1, 1, 1, 1}},
        {// Test 5
         {1, 0, 0, 0, 0},
         {1, 0, 1, 1, 0},
         {1, 0, 1, 0, 0},
         {0, 0, 1, 0, 0}}};

    std::vector<int> expected = {6, 0, 1, 12, 4};

    std::cout << "========== maxAreaOfIsland 测试 ==========\n";

    Solution solution;

    for (size_t i = 0; i < sn.size(); ++i) {
        std::cout << "Test Case " << i + 1 << " (" << sn[i] << "):\n";

        // 构建输入字符串显示
        std::string inputStr = "";
        for (size_t r = 0; r < inputs[i].size(); ++r) {
            if (r > 0) inputStr += "\n          ";
            inputStr += "[";
            for (size_t c = 0; c < inputs[i][r].size(); ++c) {
                if (c > 0) inputStr += ",";
                inputStr += std::to_string(inputs[i][r][c]);
            }
            inputStr += "]";
        }

        int result = solution.maxAreaOfIsland(inputs[i]);

        std::cout << "Input:    " << inputStr << "\n";
        std::cout << "Result:   " << result << "\n";
        std::cout << "Expected: " << expected[i] << "\n";
        std::cout << "Status:   " << (result == expected[i] ? "PASS" : "FAIL")
             << "\n";
        std::cout << "------------------------------------\n";
    }

    return 0;
}