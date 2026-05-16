/*
    快排非递归（显式栈模拟调用栈）

    核心思路：
      递归快排 = 系统自动管理  →  非递归快排 = 手动管理
                   调用栈                        显式栈

    对比：
      递归版：quick_sort(left, right) {
                  pos = partition(left, right)
                  quick_sort(left, pos-1)      ← 系统压栈
                  quick_sort(pos+1, right)     ← 系统压栈
              }

      非递归版：stack.push({left, right})
               while 栈不空:
                   {l, r} = stack.pop()
                   pos = partition(l, r)
                   stack.push({l, pos-1})      ← 手动压栈
                   stack.push({pos+1, r})      ← 手动压栈

    流程：
        开始
        │
        ├─ stack.push({left, right})
        │
        └─► stack 为空？──是──► 结束
            │否
            │弹出栈顶区间 [l, r]
            │
            ├─ l >= r？──是──► 跳过（长度为1或空，无需处理）
            │否
            │
            ├─ partition(arr, l, r)   ← 确定 pivot 最终位置
            │   返回 pos
            │
            ├─ push({l, pos-1})       ← 先处理左边
            └─ push({pos+1, r})       ← 后处理右边
            │
            └─► 回到循环顶部

    注意：
      压栈顺序不影响正确性。
      这里先压左边再压右边，pop 时会先处理右边（LIFO）。
      如果想先处理左边，交换压栈顺序即可。
*/
#include <stack>
#include <utility>

int partition(int* arr, int l, int r){
    int pivot = arr[r];
    int i = l;
    for(int j = l; j <= r - 1; ++j){
        if (arr[j] < pivot){
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}

void quick_sort_iterative(int* arr, int left, int right) {
    std::stack<std::pair<int, int>> s;
    s.push({left, right});

    while (!s.empty()) {
        auto [l, r] = s.top();
        s.pop();
        if (l >= r) continue;

        int pos = partition(arr, l, r);
        s.push({l, pos - 1});
        s.push({pos + 1, r});
    }
}
