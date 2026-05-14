// Dijkstra 算法（优先队列优化），用于计算单源最短路径
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

#define MAXN 50

struct edge {
    int v, w;
};

// 优先队列中的节点：dis 为当前最短距离，u 为顶点编号
// 重载 operator> 使得堆为小顶堆（距离小的优先级高）
struct node {
    int dis, u;

    bool operator>(const node& a) const { return dis > a.dis; }
};

// e[u] 存储从 u 出发的所有边
vector<edge> e[MAXN];
// dis[u] 存储起点到 u 的最短距离，vis[u] 标记顶点是否已确定最短距离
int dis[MAXN], vis[MAXN];
// 小顶堆优先队列，使用 vector 作为底层容器，greater<node> 比较器实现升序
//   greater<node>  : 比较器，使得 top() 返回最小的元素（默认 less 返回最大元素）
priority_queue<node, vector<node>, greater<node>> q;

// n：顶点个数（编号从 1 到 n），s：源点编号
/*
            开始
            │
            ├─ 初始化 dis[s]=0，其余 dis=∞，vis 全 false
            ├─ 将 (0, s) 压入优先队列
            │
            └─► 优先队列为空？──是──► 结束
                │否
                │弹出堆顶 (d, u)
                │
                ├─ vis[u] == true？──是──► 忽略，继续循环（惰性删除）
                │否
                │标记 vis[u] = true  （确定 u 的最短距离 = d）
                │
                └─► 遍历 u 的所有邻接边 (v, w)
                        │
                        └─► 如果 dis[v] > dis[u] + w
                            │是
                            │更新 dis[v] = dis[u] + w
                            │将 (dis[v], v) 压入堆中
                            │否 → 跳过
                │
                └─► 回到循环顶部
*/
void dijkstra(int n, int s) {
    // 初始化距离为无穷大（0x3f3f3f3f），访问标记为 false
    memset(dis, 0x3f, (n + 1) * sizeof(int));
    memset(vis, 0, (n + 1) * sizeof(int));
    dis[s] = 0;
    q.push({0, s}); // 源点入队
    while (!q.empty()) {
        int u = q.top().u; // 取出当前距离最小的顶点
        q.pop();
        if (vis[u]) continue; // 若已确定最短距离则跳过（惰性删除）
        vis[u] = 1;           // 标记为已确定
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            // 松弛操作：如果经过 u 到 v 的距离更短，则更新
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v}); // 新距离入队（允许重复入队）
            }
        }
    }
}

int main() {
    int n = 5;  // 顶点 1~5
    int s = 1;  // 起点

    // 构建邻接表（这里演示一个有向图）
    e[1].push_back({2, 2});
    e[1].push_back({3, 5});
    e[2].push_back({3, 1});
    e[2].push_back({4, 7});
    e[3].push_back({4, 2});
    e[4].push_back({5, 3});

    // 调用 Dijkstra
    dijkstra(n, s);

    // 输出结果
    for (int i = 1; i <= n; i++) {
        if (dis[i] == 0x3f3f3f3f)
            cout << "s -> " << i << " : unreachable\n";
        else
            cout << "s -> " << i << " : " << dis[i] << "\n";
    }
    return 0;
}