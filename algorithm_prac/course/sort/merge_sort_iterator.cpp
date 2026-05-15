#include <algorithm>
#include <cstring>
#define MAXA 1024

void merge(const int* aBegin, const int* aEnd, const int* bBegin,
           const int* bEnd, int* c) {
    while (aBegin != aEnd && bBegin != bEnd) {
        if (*bBegin < *aBegin) {
            *c = *bBegin;
            ++bBegin;
        } else {
            *c = *aBegin;
            ++aBegin;
        }
        ++c;
    }
    for (; aBegin != aEnd; ++aBegin, ++c) *c = *aBegin;
    for (; bBegin != bEnd; ++bBegin, ++c) *c = *bBegin;
}

void sort(int* arr, int len) {
    int* temp = new int[len];
    for (int size = 1; size < len; size *= 2) {
        for (int left = 0; size < len; left += size * 2) {
            int mid = std::min(left + size, len);
            int right = std::min(left + 2 * size, len);
            if (mid >= len) break;
            merge(arr + left, arr + mid, arr + mid, arr + right, temp + left);
        }
        std::memcpy(arr, temp, len * sizeof(int));
    }
    delete[] temp;
}