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
    int size = 1;
    while (size <= len) {
        //
    }
}