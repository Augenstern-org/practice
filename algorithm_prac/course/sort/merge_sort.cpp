#define MAXA 1024

void merge(const int* aBegin, const int* aEnd, 
           const int* bBegin, const int* bEnd, int* c) {
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

void sort(int* arr, int start, int end) {
    if(end - start <= 1) return;
    int mid = start + ((end - start) >> 1);
    sort(arr, start, mid), sort(arr, mid, end);

    int temp[MAXA];
    merge(arr + start, arr + mid, arr + mid, arr + end, temp + start);
    for (int i = start; i < end; ++i) arr[i] = temp[i];
}