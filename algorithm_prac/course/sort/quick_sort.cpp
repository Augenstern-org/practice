/*
    快排(quick_sort) —— 分治思想

    核心原理：
      每一轮 partition 都能确定基准(pivot)的最终位置，
      因为 partition 保证 pivot 左边全是 ≤ pivot 的元素，
      右边全是 > pivot 的元素。
      递归处理左右子数组，所有元素都到达最终位置 → 排序完成。

    整体流程：
        开始
        │
        └─► quick_sort(arr, left, right)
            │
            ├─ left >= right？──是──► 返回（长度为 1 或空，天然有序）
            │否
            │
            ├─ 执行 partition(arr, left, right)
            │      │
            │      ├─ 选一个元素作为基准 pivot
            │      ├─ 将数组重排，使得：
            │      │    [left,  pos-1]  全部 ≤ pivot  （左边区域）
            │      │    pos              就是 pivot   （已归位）
            │      │    [pos+1, right]   全部 > pivot  （右边区域）
            │      │
            │      └─ 返回 pivot 的位置 pos
            │
            ├─ quick_sort(arr, left, pos-1)    ← 递归排左边
            └─ quick_sort(arr, pos+1, right)   ← 递归排右边


    partition 流程（Lomuto 版本）：
        输入：区间 [left, right]
        pivot = arr[right]    （选最后一个元素作为基准）
        i = left              （i 维护 ≤ pivot 区域的右边界）

        └─► j 从 left 遍历到 right-1
            │
            ├─ arr[j] ≤ pivot？──否──► j++，继续
            │是
            │交换 arr[i] 和 arr[j]   （把 ≤ pivot 的元素换到左边去）
            │i++
            │j++
            │
            └─► 遍历结束

        交换 arr[i] 和 arr[right]    ← 把 pivot 放到正确位置
        返回 i                      ← pivot 的最终位置

        循环不变量：
          每一时刻，[left, i-1] 都是 ≤ pivot 的元素
                   [i,  j-1 ] 都是 > pivot 的元素
          遍历过程中这个性质始终成立


    为什么快排能保证正确？
      1. partition 之后，pivot 到达最终位置（左边全 ≤ 它，右边全 > 它）
      2. 递归处理左右子数组，子数组内部的排序不会破坏这个性质
      3. 当子数组长度为 1 时，它自然有序
      4. 数学归纳：每一层每个子数组至少确定一个元素的最终位置，
         最多 n 层后所有元素归位
*/
#include <algorithm>

int partition(int* arr, int l, int r){
    int pivot = arr[r];
    int i = l;
    for(int j = l; j <= r - 1; ++j){
        if(arr[j] < pivot){
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}

void quick_sort(int* arr, int left, int right) {
    if(left >= right) return;

    int pos = partition(arr, left, right);
    quick_sort(arr, left, pos - 1);
    quick_sort(arr, pos + 1, right);
}
