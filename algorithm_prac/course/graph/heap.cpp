#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

class Heap {
    std::vector<int> data;
    int left_child(int i) const { return (i << 1) + 1; }
    int right_child(int i) const { return (i << 1) + 2; }
    int parent(int i) const { return (i - 1) >> 1; }

  public:
    Heap() {}
    void swap(int i, int j) { std::swap(data[i], data[j]); }

    void heapify_down(int i, int heap_size) {
        while (true) {
            int largest = i;
            int l = left_child(i);
            int r = right_child(i);

            if (l < heap_size && data[l] > data[largest]) largest = l;
            if (r < heap_size && data[r] > data[largest]) largest = r;
            if (largest == i) break;

            swap(i, largest);
            i = largest;
        }
    }

    void build_heap(const std::vector<int>& arr) {
        if (arr.empty()) {
            data.clear();
            return;
        }
        data = arr;
        int size = data.size();
        int last_node = (size / 2) - 1;
        for (int i = last_node; i >= 0; --i) {
            heapify_down(i, size);
        }
    }

    const std::vector<int>& get_data() const { return data; }
    int heap_size() const { return data.size(); }
};

void heap_sort(std::vector<int>& arr) {
    Heap h;
    h.build_heap(arr);
    int heap_size = h.heap_size();
    for (int i = heap_size - 1; i >= 0; --i) {
        h.swap(i, 0);
        --heap_size;
        h.heapify_down(0, heap_size);
    }
}

// ============================================================
// 验证最大堆性质
// ============================================================
bool verify_max_heap(const std::vector<int>& data, int heap_size) {
    for (int i = 0; i < heap_size; ++i) {
        int l = (i << 1) + 1;
        int r = (i << 1) + 2;
        if (l < heap_size && data[l] > data[i]) return false;
        if (r < heap_size && data[r] > data[i]) return false;
    }
    return true;
}

int main() {
    // ============================================================
    // 1. 基本测试用例
    // ============================================================
    std::vector<std::vector<int>> tests = {
        {4, 10, 3, 5, 1}, {1, 2, 3, 4, 5},  {5, 4, 3, 2, 1}, {7}, {},
        {4, 1, 4, 2, 4},  {10, -1, 3, 0, 2}};

    std::cout << "TESTS" << std::endl;
    std::cout << "========================================" << std::endl;
    for (const auto& arr : tests) {
        Heap h;
        h.build_heap(arr);

        // 直接取 data
        const auto& data = h.get_data();
        bool ok = verify_max_heap(data, data.size());

        std::cout << "Input:    ";
        for (int x : arr) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "Heap:     ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "Heap property? " << (ok ? "YES" : "NO") << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    // ============================================================
    // 2. 随机数据测试 + 计时
    // ============================================================
    std::cout << std::endl;
    std::cout << "RANDOM TESTS (build_heap only)" << std::endl;
    std::cout << "========================================" << std::endl;

    // 随机数引擎
    std::mt19937 rng(42); // 固定种子以保证可复现
    std::uniform_int_distribution<int> dist(0, 100000);

    std::vector<int> sizes = {100, 1000, 5000, 10000, 50000};

    for (int n : sizes) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) data[i] = dist(rng);

        Heap h;
        auto start = std::chrono::steady_clock::now();
        h.build_heap(data);
        auto end = std::chrono::steady_clock::now();

        double elapsed = std::chrono::duration<double>(end - start).count();
        bool ok = verify_max_heap(h.get_data(), h.get_data().size());

        std::cout << "n = " << n << std::endl;
        std::cout << "  Heap property? " << (ok ? "YES" : "NO") << std::endl;
        std::cout << "  Build time:    " << elapsed << " s" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    return 0;
}
