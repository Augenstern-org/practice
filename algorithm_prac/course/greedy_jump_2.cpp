#include <iostream>

int test[4] = {1, 2, 0, 1};
int size = sizeof(test) >> 2;

void print(int* array, int limit) {
    std::cout << "Array: " << "[ ";
    for (int i = 0; i != limit - 1; ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << array[limit - 1] << " ]" << std::endl;
}

int max(int start, int end, int* array, int limit) {
    int res = 0;
    for (int i = start; i < limit && i != end + 1; ++i) {
        res = res > array[i] ? res : array[i];
    }
    return res;
}

// int solve(int* a, int limit) {
//     int pos = 0;
//     // int range = 0;
//     int cnt = 1;
//     while (pos <= pos + a[pos] && pos + a[pos] < limit - 1) {
//         pos += max(pos + 1, pos + a[pos], a, limit);
//         ++cnt;
//     }
//     return cnt;
// }

int solve(int* a, int limit) {
    int cnt = 0, end = 0, farthest = 0;
    for (int i = 0; i < limit - 1; ++i) {
        farthest = farthest > i + a[i] ? farthest : i + a[i];
        if (i == end) {
            if (farthest == end) return -1;
            end = farthest;
            ++cnt;
        }
    }
    return cnt;
}

int main() {
    std::cout << "size: " << size << std::endl;
    print(test, size);
    std::cout << "Steps: " << solve(test, size) << std::endl;
}