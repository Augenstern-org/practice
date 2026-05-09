#include <iostream>

int test[3] = {1,2,3};
int size = sizeof(test) >> 2;

void print(int* array, int limit) {
    std::cout << "Array: " << "[ ";
    for (int i = 0; i != limit - 1; ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << array[limit - 1] << " ]" << std::endl;
}

bool solve(int* a, int limit) {
    int range = 0;
    int pos = 0;
    do {
        range = a[pos] + pos > range ? a[pos] + pos : range;
        ++pos;
    } while (range >= pos && range < limit);
    if (range >= limit - 1) return true;
    return false;
}
int main() {
    std::cout << "size: " << size << std::endl;
    print(test, size);
    std::cout << "Can reach the end: \n"
              << (solve(test, size) == 1 ? "true" : "false") << std::endl;
}