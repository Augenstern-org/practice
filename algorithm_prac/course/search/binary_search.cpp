#include <chrono>
#include <iostream>
#include <vector>

std::vector<int>::const_iterator search(const std::vector<int>& arr,
                                        int target) {
    std::vector<int>::const_iterator beg = arr.begin();
    std::vector<int>::const_iterator end = arr.end();
    std::vector<int>::const_iterator mid = beg + (end - beg) / 2;
    for (; *mid != target && beg != end; mid = beg + (end - beg) / 2) {
        if (target > *mid) beg = mid;
        if (target < *mid) end = mid;
    }
    if (beg == end) return arr.end();
    return mid;
}

std::vector<int> test{1, 2, 3, 4, 5, 6, 7, 8, 9};

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    auto res = search(test, 2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();

    std::cout << *res << "\n" << &res << std::endl;
    std::cout << "执行时间: " << duration << " 纳秒" << std::endl;
}