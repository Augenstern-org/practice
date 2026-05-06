#include <iostream>
#include <vector>
#include <random>
#include <chrono>

std::vector<int> solve(std::vector<int> target) {
    int l = 0, r = 0, sum = 0;
    std::vector<int> res{-1, -1, 0};
    while (r != target.size()) {
        sum += target[r];
        if (sum <= 0) {
            if (sum - target[r] > res[2]) {
                res[2] = sum - target[r];
                res[0] = l;
                res[1] = r - 1;
            }
            sum = 0;
            l = r;
            while (l!=target.size() && target[l] <= 0) ++l;
            r = l;
        } else
            ++r;
    }
    if (sum > res[2]) {
        res[2] = sum;
        res[0] = l;
        res[1] = r - 1;
    }
    return res;
}

std::vector<int> solve_2(std::vector<int> target){
    int max_sum = target[0], sum = target[0];
    int start = 0, end = 0;
    int t_start = 0;
    for(size_t i = 1; i != target.size(); ++i){
        if(sum < 0){
            sum = target[i];
            t_start = i;
        } else {
            sum += target[i];
        }
        if(sum > max_sum){
            max_sum = sum;
            start = t_start;
            end = i;
        }
    }
    return {start, end, max_sum};
}

int main() {
    // 输入长度
    int n;
    std::cout << "请输入要生成的数据个数: ";
    std::cin >> n;

    // 生成随机数 [0, 1000000]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000000);
    std::vector<int> test_data(n);
    for (int i = 0; i < n; ++i) {
        test_data[i] = dist(gen);
    }

    std::cout << "test_data (前10个):";
    for (int i = 0; i < std::min(10, n); ++i) {
        std::cout << " " << test_data[i];
    }
    std::cout << (n > 10 ? " ..." : "") << std::endl;

    // 计时
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> ans = solve_2(test_data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "max_sum: " << ans[2] << "\nindex: \nl: " << ans[0]
              << " r: " << ans[1] << std::endl;
    std::cout << "执行时间: " << duration << " 微秒" << std::endl;
    return 0;
}